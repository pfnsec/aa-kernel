#ifndef PL181_H
#define PL181_H

typedef volatile struct pl181 {
	uint32_t power;
	uint32_t clock;
	uint32_t cmd_arg;
	uint32_t cmd;
	uint32_t resp_cmd;
	uint32_t resp0;
	uint32_t resp2;
	uint32_t resp3;
	uint32_t resp4;
	uint32_t data_timer;
	uint32_t data_len;
	uint32_t data_control;
	uint32_t data_counter;
	uint32_t status;
	uint32_t clear;
	uint32_t pad0;
	uint32_t fifo_counter;
	uint32_t pad1;
	uint32_t data_fifo;
} pl181;


//pl181->power 
#define PL181_POWER_OFF  0
#define PL181_POWER_UP   2
#define PL181_POWER_ON   3

//pl181->cmd
#define PL181_WAIT_RESP     (1 << 6)
#define PL181_LONG_RESP     (1 << 7)
#define PL181_WAIT_IRQ      (1 << 8)
#define PL181_CPSM_PEND     (1 << 9)
#define PL181_CPSM_EN       (1 << 10)

//pl181->data_control
#define PL181_DATA_EN       (1 << 0)
#define PL181_DATA_READ     (1 << 1)
#define PL181_DATA_STREAM   (1 << 2)

//pl181->status, pl181->clear[0:10]
#define PL181_CMD_CRC_FAIL  (1 << 0)
#define PL181_DATA_CRC_FAIL (1 << 1)
#define PL181_CMD_TIMEOUT   (1 << 2)
#define PL181_DATA_TIMEOUT  (1 << 3)
#define PL181_TX_UNDERRUN   (1 << 4)
#define PL181_RX_OVERRUN    (1 << 5)
#define PL181_CMD_RESP_END  (1 << 6)
#define PL181_CMD_SENT      (1 << 7)
#define PL181_RX_DATA_AVAIL (1 << 20)
#define PL181_RX_DATA_AVAIL (1 << 21)





#endif
