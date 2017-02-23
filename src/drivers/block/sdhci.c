#include "platform.h"
#include "drivers/block/sdhci.h"
#include "kernel/console.h"
#include "kernel/mutex.h"
#include "kernel/blockdev.h"


volatile int command_pending  = 0;
volatile int dma_pending      = 0;
volatile int command_error    = 0;
volatile int powerup_complete = 0;

uint32_t card_rca;
uint32_t card_csd[4];

void sdhci_card_plug(sdhci *dev);


const blk_dev_ops sdhci_ops = {
	&op_sdhci_get_volumes,
	&op_sdhci_read_block,
	&op_sdhci_sync
};


const blk_dev blk_sdhci = {
	&sdhci_ops,
	SD0
};


int op_sdhci_read_block(struct blk_dev *dev, uint32_t blk_addr, uint8_t *dest) {
	return sdhci_read_sector(dev->reg, blk_addr, dest);
}

void op_sdhci_sync(struct blk_dev *dev) {
	sdhci_dma_sync();
}

int op_sdhci_get_volumes(struct blk_dev *dev, volume *vol) {

	uint32_t c_size;
	uint16_t c_size_mult;
	uint16_t read_bl_len;
	uint32_t blocks = 0;


	if(card_csd[3] & (1 << 22)) {
		//Version 2 CSD
		c_size = ((card_csd[1]) >> 8);
		blocks = (c_size + 1) * 1000;
	} else {
		//Version 1 CSD
		printf("v1 CSD\n");
		return 0;
	}


	vol->next = 0;
	vol->subvolumes = 0;

	vol->start = 0;
	vol->end = blocks;

	printf("sd0: Found card with %w blocks \n", blocks); 

	return 0;
}


void sdhci_init(sdhci *dev) {

	dev->reset_ctrl |= SDHC_RESET_CMD | SDHC_RESET_DAT | SDHC_RESET_ALL;

	printf("SDHCI: Reset...\n");

	while(dev->reset_ctrl & (SDHC_RESET_ALL))
		;

	dev->clock_ctrl |= (0x20 << 8) | SDHC_CLK_EN;

	printf("SDHCI: Enable Clock...\n");

	while(!(dev->clock_ctrl & SDHC_CLK_STABLE))
		;


	uint32_t irq_mask = 
		( IRQ_CEATA_ERROR_STATUS
		| IRQ_TARGET_RESPONSE_ERROR
		| IRQ_ADMA_ERROR
		| IRQ_AUTO_CMD12_ERROR
		| IRQ_CURRENT_LIMIT_ERROR
		| IRQ_DATA_END_BIT_ERROR
		| IRQ_DATA_CRC_ERROR
		| IRQ_DATA_TIMEOUT_ERROR
		| IRQ_CMD_INDEX_ERROR
		| IRQ_CMD_END_BIT_ERROR
		| IRQ_CMD_CRC_ERROR
		| IRQ_CMD_TIMEOUT_ERROR
		| IRQ_CARD_REMOVAL
		| IRQ_CARD_INSERTION
		| IRQ_BUFFER_READ_READY
		| IRQ_BUFFER_WRITE_READY
		| IRQ_DMA_INTERRUPT
		| IRQ_BLOCK_GAP_EVENT
		| IRQ_TRANSFER_COMPLETE
		| IRQ_CMD_COMPLETE );

	dev->irq_status_en = IRQ_CARD_INTERRUPT;
	dev->irq_signal_en = IRQ_CARD_INTERRUPT;

	dev->irq_status_en |= irq_mask;
	dev->irq_signal_en |= irq_mask;

	sdhci_card_plug(dev);

}


int sdhci_command_start(sdhci *dev, uint8_t cmd, uint32_t arg, sdhci_resp *resp){

	while(dev->present_state & (CMD_INHIBIT_DAT | CMD_INHIBIT_CMD))
		;

	dev->timeout_ctrl = 0xE;
	dev->blk_size = 0x0200;
	dev->blk_count = 1;
	dev->arg = arg;
	dev->trx_mode = TRX_READ | TRX_SINGLE_BLK;

	switch(cmd) {
	case(MMC_GO_IDLE_STATE):
		dev->command = (cmd << 8);
		break;
	case(MMC_SEND_OP_COND):
		dev->command = (cmd << 8) | RESP_R3;
		break;
	case(MMC_ALL_SEND_CID):
		dev->command = (cmd << 8) | CRC_ENABLE | RESP_136;
		break;
	case(MMC_SET_RELATIVE_ADDR):
		dev->command = (cmd << 8) | RESP_R1;
		break;
	case(MMC_SET_DSR):
		dev->command = (cmd << 8);
		break;
	case(MMC_SWITCH):
		dev->command = (cmd << 8) | RESP_R1b;
		break;
	case(MMC_SELECT_CARD):
		dev->command = (cmd << 8) | RESP_R1;
		break;
	case(MMC_SEND_EXT_CSD):
		dev->command = (cmd << 8) | RESP_R1;
		break;
	case(MMC_SEND_CSD):
	case(MMC_SEND_CID):
		dev->command = (cmd << 8) | CRC_ENABLE | RESP_136;
		break;
	case(MMC_READ_DAT_UNTIL_STOP):
		dev->command = (cmd << 8) | RESP_R1;
		break;
	case(MMC_STOP_TRANSMISSION):
		dev->command = (cmd << 8) | RESP_R1b;
		break;
	case(MMC_SEND_STATUS):
	case(MMC_BUS_TEST_R):
		dev->command = (cmd << 8) | RESP_R1;
		break;
	case(MMC_GO_INACTIVE_STATE):
		dev->command = (cmd << 8);
		break;
	case(MMC_BUS_TEST_W):
	case(MMC_SET_BLOCKLEN):
	case(MMC_READ_SINGLE_BLOCK):
		dev->trx_mode = TRX_READ | TRX_SINGLE_BLK | DMA_ENABLE;
		dev->command = (cmd << 8) | DATA_PRESENT | RESP_R1;
		break;
	case(MMC_READ_MULTIPLE_BLOCK):
	case(MMC_WRITE_DAT_UNTIL_STOP):
	case(MMC_SET_BLOCK_COUNT):
	case(MMC_WRITE_BLOCK):
	case(MMC_WRITE_MULTIPLE_BLOCK):
	case(MMC_PROGRAM_CID):
	case(MMC_PROGRAM_CSD):
		dev->command = (cmd << 8) | RESP_R1;
		break;
	case(MMC_SET_WRITE_PROT):
	case(MMC_CLR_WRITE_PROT):
		dev->command = (cmd << 8) | RESP_R1b;
		break;
	case(MMC_SEND_WRITE_PROT):
	case(MMC_ERASE_GROUP_START):
	case(MMC_ERASE_GROUP_END):
		dev->command = (cmd << 8) | RESP_R1;
		break;
	case(MMC_ERASE):
		dev->command = (cmd << 8) | RESP_R1b;
		break;
	case(MMC_APP_CMD):
	case(MMC_GEN_CMD):
		dev->command = (cmd << 8) | RESP_R1;
		break;

	case(41):
		dev->command = (cmd << 8) | RESP_48;
		break;

	default:	
		command_pending = 0;
		return 1;

	}


	command_error = 0;
	command_pending = 1;

	while(command_pending)
		irq_wait();

	if(resp) {
		resp->command  = cmd;
		resp->response[0] = dev->resp0;
		resp->response[1] = dev->resp1;
		resp->response[2] = dev->resp2;
		resp->response[3] = dev->resp3;
	}
	

	if(command_error) {
//		sdhci_dump(dev);
	}

	return command_error;

}

int sdhci_appcommand_start(sdhci *dev, uint8_t acmd, uint32_t arg, sdhci_resp *resp){
	if(!sdhci_command_start(dev, MMC_APP_CMD, 0, resp))
		return sdhci_command_start(dev, acmd, arg, resp);
	else 
		return -1;
}

void sdhci_card_reset(sdhci *dev) {

	sdhci_resp resp;

	sdhci_command_start(dev, MMC_GO_IDLE_STATE, 0, 0);

	sdhci_command_start(dev, MMC_SEND_EXT_CSD, 0x1AA, 0);


	while(1) {
		sdhci_appcommand_start(dev, 41, 0x40300000, &resp);
		if(resp.response[0] & (1 << 31))
			break;
	}

	sdhci_command_start(dev, MMC_ALL_SEND_CID, 0, 0);

	sdhci_command_start(dev, MMC_SET_RELATIVE_ADDR, 0, &resp);

	card_rca = resp.response[0];


	sdhci_command_start(dev, MMC_SEND_CSD, card_rca, &resp);

	card_csd[0] = resp.response[0];
	card_csd[1] = resp.response[1];
	card_csd[2] = resp.response[2];
	card_csd[3] = resp.response[3];


	sdhci_command_start(dev, MMC_SELECT_CARD, card_rca, 0);

}


int sdhci_read_sector(sdhci *dev, uint32_t blk_addr, void *addr) {

	sdhci_resp resp;

	dma_pending = 1;
	dev->sdma_addr = (uint32_t) addr;

	while(!powerup_complete)
		irq_wait();

	return sdhci_command_start(dev, MMC_READ_SINGLE_BLOCK, blk_addr, &resp);

}

void sdhci_dma_sync() {
	while(dma_pending)
		irq_wait();
}


void sdhci_card_powerup(sdhci *dev) {

	if(dev->capabilities & SDHC_CAP_33V) {
		dev->pwr_ctrl = SD_BUS_POWER_33V;
	} else if(dev->capabilities & SDHC_CAP_30V) {
		dev->pwr_ctrl = SD_BUS_POWER_30V;
	} else {
		printf("SDHC: Powerup failed!\n)");
		return;
	}


	dev->pwr_ctrl |= SD_BUS_POWER_EN;
		

	//Enable card clock
	dev->clock_ctrl |= SD_CLK_EN;


	printf("SD Powered Up...\n");
}


void sdhci_card_powerdown(sdhci *dev) {

	while(dev->present_state & (CMD_INHIBIT_DAT | CMD_INHIBIT_CMD))
		;
	
	//Disable card clock
	dev->clock_ctrl &= ~SD_CLK_EN;
	
	dev->pwr_ctrl &= ~SD_BUS_POWER_EN;

	printf("SD Powered Down...\n");
}


//Handle card insertion/removal - Call with IRQ_CARD_INTERRUPT disabled!
void sdhci_card_plug(sdhci *dev) {
	if(dev->present_state & CARD_INSERTED) {
		sdhci_card_powerup(dev);
	} else { 
		sdhci_card_powerdown(dev);
	}
}

void sdhci_isr(sdhci *dev) {
//	printf("%w : ", dev->irq_status);

	if(dev->irq_status & IRQ_ERROR_INTERRUPT) {
		printf("SD Error: ");
		if(dev->irq_status & IRQ_CMD_INDEX_ERROR) {
			dev->irq_status |= IRQ_CMD_INDEX_ERROR;
			printf("Command Index Error ");
		} else if(dev->irq_status & IRQ_CURRENT_LIMIT_ERROR) {
			dev->irq_status |= IRQ_CURRENT_LIMIT_ERROR;
			printf("Power Failure! ");
			sdhci_card_powerdown(dev);

		} else if(dev->irq_status & IRQ_DATA_END_BIT_ERROR) {
			dev->irq_status |= IRQ_DATA_END_BIT_ERROR;
			printf("Data End Bit Error ");
		} else if(dev->irq_status & IRQ_DATA_CRC_ERROR) {
			dev->irq_status |= IRQ_DATA_CRC_ERROR;
			printf("Data CRC Error ");
		} else if(dev->irq_status & IRQ_DATA_TIMEOUT_ERROR) {
			dev->irq_status |= IRQ_DATA_TIMEOUT_ERROR;
			printf("Data Timeout Error ");

		} else if(dev->irq_status & IRQ_CMD_END_BIT_ERROR) {
			dev->irq_status |= IRQ_CMD_END_BIT_ERROR;
			printf("Command End Bit Error ");
		} else if(dev->irq_status & IRQ_CMD_CRC_ERROR) {
			dev->irq_status |= IRQ_CMD_CRC_ERROR;
			printf("Command CRC Error ");
		} else if(dev->irq_status & IRQ_CMD_TIMEOUT_ERROR) {
			dev->irq_status |= IRQ_CMD_TIMEOUT_ERROR;
			printf("Command Timeout Error ");
		}	

		printf("%w ",  dev->resp3);
		printf("%w ",  dev->resp2);
		printf("%w ",  dev->resp1);
		printf("%w\n", dev->resp0);

		dev->irq_status |= IRQ_ERROR_INTERRUPT;

		command_error = 1;

		__dmb();

		command_pending = 0;

	} else if(dev->irq_status & IRQ_CMD_COMPLETE) {

		dev->irq_status |= IRQ_CMD_COMPLETE;

		printf("SD Command Complete ");
		printf("%w ",  dev->resp3);
		printf("%w ",  dev->resp2);
		printf("%w ",  dev->resp1);
		printf("%w\n", dev->resp0);

		command_error = 0;

		__dmb();

		command_pending = 0;

	} else if(dev->irq_status & IRQ_CARD_INTERRUPT) {

		printf("SD Card Interrupt\n");
		dev->irq_status |= IRQ_CARD_INTERRUPT;

	} else if(dev->irq_status & IRQ_CARD_INSERTION) {

		sdhci_card_plug(dev);
		printf("SD Card Insert\n");
		dev->irq_status |= IRQ_CARD_INSERTION;

	} else if(dev->irq_status & IRQ_CARD_REMOVAL) {

		sdhci_card_plug(dev);
		printf("SD Card Remove\n");
		dev->irq_status |= IRQ_CARD_REMOVAL;

		command_pending = 0;

	} else if(dev->irq_status & IRQ_BUFFER_WRITE_READY) {
		printf("SD Buffer Write Ready\n");

		for(int i = 0; i < 512; i++) {
		}

		dev->irq_status |= IRQ_BUFFER_WRITE_READY;
	} else if(dev->irq_status & IRQ_BUFFER_READ_READY) {
		printf("SD Buffer Read Ready\n");

		for(int i = 0; i < 512; i++) {
			while((dev->present_state & BUFFER_READ_EN)) {
				printf("%w \n",  dev->buffer_data_port);
			}
		}

		dev->irq_status |= IRQ_BUFFER_READ_READY;

	} else if(dev->irq_status & IRQ_DMA_INTERRUPT) {

		printf("DMA Interrupt\n");
		dev->irq_status |= IRQ_DMA_INTERRUPT;

		command_pending = 0;

	} else if(dev->irq_status & IRQ_TRANSFER_COMPLETE) {

		printf("Transfer Complete\n");
		dev->irq_status |= IRQ_TRANSFER_COMPLETE;

		dma_pending = 0;

	}
}


void sdhci_dump(sdhci *dev) {
	printf("sdma_addr     : 0x%w\n", dev->sdma_addr);
	printf("block_size    : 0x%h\n", dev->blk_size);
	printf("block_count   : 0x%h\n", dev->blk_count);
	printf("arg           : 0x%w\n", dev->arg);
	printf("trx_mode      : 0x%h\n", dev->trx_mode);
	printf("command       : 0x%h\n", dev->command);
	printf("resp0         : 0x%w\n", dev->resp0);
	printf("resp1         : 0x%w\n", dev->resp1);
	printf("resp2         : 0x%w\n", dev->resp2);
	printf("resp3         : 0x%w\n", dev->resp3);
	printf("buf_data_port : 0x%w\n", dev->buffer_data_port);
	printf("present_state : 0x%w\n", dev->present_state);
        printf("host_ctrl     : 0x%b\n", dev->host_ctrl);
        printf("pwr_ctrl      : 0x%b\n", dev->pwr_ctrl);
        printf("blk_gap_ctrl  : 0x%b\n", dev->blk_gap_ctrl);
        printf("wakeup_ctrl   : 0x%b\n", dev->wakeup_ctrl);
	printf("clock_ctrl    : 0x%h\n", dev->clock_ctrl);
	printf("timeout_ctrl  : 0x%b\n", dev->timeout_ctrl);
	printf("reset_ctrl    : 0x%b\n", dev->reset_ctrl);
	printf("irq_status    : 0x%w\n", dev->irq_status);
        printf("irq_status_en : 0x%w\n", dev->irq_status_en);
	printf("irq_signal_en : 0x%w\n", dev->irq_signal_en);
	printf("capabilities  : 0x%w\n", dev->capabilities);
	printf("spi_int       : 0x%w\n", dev->spi_int);
	printf("slot_int      : 0x%w\n", dev->slot_int);
}


