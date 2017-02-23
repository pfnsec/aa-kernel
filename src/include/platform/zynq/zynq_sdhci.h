#ifndef ZYNQ_SDHCI_H
#define ZYNQ_SDHCI_H
#include <stdint.h>

typedef volatile struct zynq_sdhci {
	uint32_t sdma_addr;
	uint16_t blk_size;
	uint16_t blk_count;
	uint32_t arg;
	uint16_t trx_mode;
	uint16_t command;
	uint32_t resp0;
	uint32_t resp1;
	uint32_t resp2;
	uint32_t resp3;
	uint32_t buffer_data_port;
	uint32_t present_state;
        uint8_t  host_ctrl;
        uint8_t  pwr_ctrl;
        uint8_t  blk_gap_ctrl;
        uint8_t  wakeup_ctrl;
	uint16_t clock_ctrl;
	uint8_t  timeout_ctrl;
	uint8_t  reset_ctrl;
	uint32_t irq_status;
        uint32_t irq_status_en;
	uint32_t irq_signal_en;
	uint16_t auto_cmd12_error;
	uint16_t pad0;
	uint32_t capabilities;
	uint32_t pad1;
	uint32_t max_current;
	uint32_t pad2;
	uint32_t force_event;
	uint32_t adma_error;
	uint32_t adma_addr;
	uint32_t pad3;
	uint32_t boot_timeout;
	uint32_t debug;
	uint32_t pad4[0x22];
	uint32_t spi_int;
	uint32_t pad5;
	uint32_t slot_int;
} __attribute__((packed, aligned(4))) zynq_sdhci;


//zynq_sdhci->trx_mode fields
#define DMA_ENABLE        (1 << 0)
#define BLK_CNT_ENABLE    (1 << 1)
#define AUTO_CMD12_ENABLE (1 << 2)

#define TRX_WRITE         (0 << 4)
#define TRX_READ          (1 << 4)

#define TRX_SINGLE_BLK    (0 << 5)
#define TRX_MULTI_BLK     (1 << 5)

//zynq_sdhci->command fields
#define DATA_PRESENT      (1 << 5)
#define INDEX_CHECK       (1 << 4)
#define CRC_ENABLE        (1 << 3)
#define RESP_48           (1 << 1)
#define RESP_136          (1 << 0)

//zynq_sdhci->present_state fields
#define CARD_INSERTED     (1 << 16)
#define BUFFER_READ_EN    (1 << 11)
#define CMD_INHIBIT_DAT   (1 << 1)
#define CMD_INHIBIT_CMD   (1 << 0)

//zynq_sdhci->host_control fields
#define SDHC_HIGH_SPEED   (1 << 2)
#define SDHC_4BIT         (1 << 1)

//zynq_sdhci->power_control fields
#define SD_BUS_POWER_EN   (1 << 0)
#define SD_BUS_POWER_33V  (7 << 1)
#define SD_BUS_POWER_30V  (6 << 1)
#define SD_BUS_POWER_18V  (5 << 1)

//zynq_sdhci->clock_control fields
#define SD_CLK_EN         (1 << 2)
#define SDHC_CLK_STABLE   (1 << 1)
#define SDHC_CLK_EN       (1 << 0)

//zynq_sdhci->reset_ctrl fields
#define SDHC_RESET_DAT    (1 << 2)
#define SDHC_RESET_CMD    (1 << 1)
#define SDHC_RESET_ALL    (1 << 0)

//zynq_sdhci->capabilities fields
#define SDHC_CAP_18V      (1 << 26)
#define SDHC_CAP_30V      (1 << 25)
#define SDHC_CAP_33V      (1 << 24)


//IRQ Bitmasks

#define IRQ_CEATA_ERROR_STATUS       (1 << 29) 
#define IRQ_TARGET_RESPONSE_ERROR    (1 << 28) 
#define IRQ_ADMA_ERROR               (1 << 25) 
#define IRQ_AUTO_CMD12_ERROR         (1 << 24) 
#define IRQ_CURRENT_LIMIT_ERROR      (1 << 23) 
#define IRQ_DATA_END_BIT_ERROR       (1 << 22) 
#define IRQ_DATA_CRC_ERROR           (1 << 21) 
#define IRQ_DATA_TIMEOUT_ERROR       (1 << 20) 
#define IRQ_CMD_INDEX_ERROR          (1 << 19) 
#define IRQ_CMD_END_BIT_ERROR        (1 << 18) 
#define IRQ_CMD_CRC_ERROR            (1 << 17) 
#define IRQ_CMD_TIMEOUT_ERROR        (1 << 16) 
#define IRQ_ERROR_INTERRUPT          (1 << 15) 
#define IRQ_BOOT_TERMINATE           (1 << 10) 
#define IRQ_BOOT_ACK_RCV             (1 << 9) 
#define IRQ_CARD_INTERRUPT           (1 << 8) 
#define IRQ_CARD_REMOVAL             (1 << 7) 
#define IRQ_CARD_INSERTION           (1 << 6) 
#define IRQ_BUFFER_READ_READY        (1 << 5) 
#define IRQ_BUFFER_WRITE_READY       (1 << 4) 
#define IRQ_DMA_INTERRUPT            (1 << 3) 
#define IRQ_BLOCK_GAP_EVENT          (1 << 2) 
#define IRQ_TRANSFER_COMPLETE        (1 << 1) 
#define IRQ_CMD_COMPLETE             (1 << 0) 



//MMC Commands                           type  argument     response */
//Basic (Class 0)
#define MMC_GO_IDLE_STATE         0   /* bc                          */
#define MMC_SEND_OP_COND          1   /* bcr  [31:0]  OCR        R3  */
#define MMC_ALL_SEND_CID          2   /* bcr                     R2  */
#define MMC_SET_RELATIVE_ADDR     3   /* ac   [31:16] RCA        R1  */
#define MMC_SET_DSR               4   /* bc   [31:16] RCA            */
#define MMC_SWITCH                6   /* ac   [31:0]  See below  R1b */
#define MMC_SELECT_CARD           7   /* ac   [31:16] RCA        R1  */
#define MMC_SEND_EXT_CSD          8   /* adtc                    R1  */
#define MMC_SEND_CSD              9   /* ac   [31:16] RCA        R2  */
#define MMC_SEND_CID             10   /* ac   [31:16] RCA        R2  */
#define MMC_READ_DAT_UNTIL_STOP  11   /* adtc [31:0]  dadr       R1  */
#define MMC_STOP_TRANSMISSION    12   /* ac                      R1b */
#define MMC_SEND_STATUS          13   /* ac   [31:16] RCA        R1  */
#define MMC_BUS_TEST_R           14   /* adtc                    R1  */
#define MMC_GO_INACTIVE_STATE    15   /* ac   [31:16] RCA            */
#define MMC_BUS_TEST_W           19   /* adtc                    R1  */

//Block Read (Class 2)
#define MMC_SET_BLOCKLEN         16   /* ac   [31:0] block len   R1  */
#define MMC_READ_SINGLE_BLOCK    17   /* adtc [31:0] data addr   R1  */
#define MMC_READ_MULTIPLE_BLOCK  18   /* adtc [31:0] data addr   R1  */
#define MMC_SEND_TUNING_BLOCK    19   /* adtc                    R1  */

  /* class 3 */
#define MMC_WRITE_DAT_UNTIL_STOP 20   /* adtc [31:0] data addr   R1  */

  /* class 4 */
#define MMC_SET_BLOCK_COUNT      23   /* adtc [31:0] data addr   R1  */
#define MMC_WRITE_BLOCK          24   /* adtc [31:0] data addr   R1  */
#define MMC_WRITE_MULTIPLE_BLOCK 25   /* adtc                    R1  */
#define MMC_PROGRAM_CID          26   /* adtc                    R1  */
#define MMC_PROGRAM_CSD          27   /* adtc                    R1  */

  /* class 6 */
#define MMC_SET_WRITE_PROT       28   /* ac   [31:0] data addr   R1b */
#define MMC_CLR_WRITE_PROT       29   /* ac   [31:0] data addr   R1b */
#define MMC_SEND_WRITE_PROT      30   /* adtc [31:0] wpdata addr R1  */

  /* class 5 */
#define MMC_ERASE_GROUP_START    35   /* ac   [31:0] data addr   R1  */
#define MMC_ERASE_GROUP_END      36   /* ac   [31:0] data addr   R1  */
#define MMC_ERASE                38   /* ac                      R1b */

  /* class 9 */
#define MMC_FAST_IO              39   /* ac   <Complex>          R4  */
#define MMC_GO_IRQ_STATE         40   /* bcr                     R5  */

  /* class 7 */
#define MMC_LOCK_UNLOCK          42   /* adtc                    R1b */

  /* class 8 */
#define MMC_APP_CMD              55   /* ac   [31:16] RCA        R1  */
#define MMC_GEN_CMD              56   /* adtc [0] RD/WR          R1  */


//Response Definitions
#define RESP_R1  (INDEX_CHECK | CRC_ENABLE | RESP_48)
#define RESP_R1b (INDEX_CHECK | CRC_ENABLE | RESP_48)
#define RESP_R2  (INDEX_CHECK | CRC_ENABLE | RESP_136)
#define RESP_R3  (INDEX_CHECK | CRC_ENABLE | RESP_48)
#define RESP_R6  (INDEX_CHECK | CRC_ENABLE | RESP_48)
#define RESP_R7  (INDEX_CHECK | CRC_ENABLE | RESP_48)


void zynq_sdhci_init(zynq_sdhci *dev);

int zynq_sdhci_read_sector(zynq_sdhci *dev, uint32_t blk_addr, void *addr);

void zynq_sdhci_isr(zynq_sdhci *dev);

void zynq_sdhci_dump(zynq_sdhci *dev);


#endif 
