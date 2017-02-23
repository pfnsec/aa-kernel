#ifndef UART_H
#define UART_H
#include <stdint.h>

typedef volatile struct zynq_uart {
	uint32_t control;
	uint32_t mode;
	uint32_t irq_en;
	uint32_t irq_dis;
	
	uint32_t irq_mask;
	uint32_t channel_irq_status;
	uint32_t baud_gen;
	uint32_t rx_timeout;

	uint32_t rx_fifo_trig_lvl;
	uint32_t modem_control;
	uint32_t modem_status;
	uint32_t channel_status;

	uint32_t tx_rx_fifo;
	uint32_t baud_rate_div;
	uint32_t flow_delay;
	uint32_t pad0;

	uint32_t pad1;
	uint32_t tx_fifo_trig_lvl;
} __attribute__((packed))  zynq_uart;


//zynq_uart->control
#define STOP_BREAK     (1 << 8)
#define START_BREAK    (1 << 7)
#define RX_TIMEOUT     (1 << 6)
#define TX_DIS         (1 << 5)
#define TX_EN          (1 << 4)
#define RX_DIS         (1 << 3)
#define RX_EN          (1 << 2)
#define TX_RESET       (1 << 1)
#define RX_RESET       (1 << 0)

//zynq_uart->mode
#define MODE_NORMAL    (0 << 8)
#define MODE_ECHO      (1 << 8)
#define MODE_LB_LOCAL  (2 << 8)
#define MODE_LB_REMOTE (3 << 8)

#define STOP_1BIT      (0 << 6)
#define STOP_1_5BIT    (1 << 6)
#define STOP_2BIT      (2 << 6)

#define PARITY_NONE    (1 << 5)

#define CHAR_8BIT      (0 << 1)
#define CHAR_7BIT      (2 << 1)
#define CHAR_6BIT      (3 << 1)

#define CLK_DIV1       (0 << 0)
#define CLK_DIV8       (1 << 0)


//zynq_uart->channel_status
#define TX_FIFO_FULL  (1 << 4)
#define TX_FIFO_EMPTY (1 << 3)
#define RX_FIFO_FULL  (1 << 2)
#define RX_FIFO_EMPTY (1 << 1)
#define RX_FIFO_TRIG  (1 << 0)


//zynq_uart->modem_control
#define FLOW_AUTO     (1 << 5)

//zynq_uart->modem_status
#define FLOW_EN       (1 << 8)


//zynq_uart->baud_gen, clock divide constants
#define BAUD_115200_CD  124

//zynq_uart->baud_rate_div
#define BAUD_115200_BDIV 6


//Add carriage return automatically (\n -> \r\n)
#define UART_EOL_CR_LF 1


void zynq_uart_init(zynq_uart *);

void zynq_uart_putc(zynq_uart *dev, char c);

char zynq_uart_getc(zynq_uart *dev);

void zynq_uart_isr();

#endif
