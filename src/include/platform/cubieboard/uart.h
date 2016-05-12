#ifndef UART_H
#define UART_H
#include <stdint.h>

typedef struct sunxi_uart {
union {	volatile uint32_t trx_buf;    uint32_t div_low; };
union {	uint32_t irq_enable; uint32_t div_hi;  };
union {	uint32_t fifo_ctl;   uint32_t irq_id;  };
	uint32_t line_ctl;
	uint32_t modem_ctl;
	uint32_t line_status;
	uint32_t modem_status;
	uint32_t scratch;
	uint32_t pad0[24];
	uint32_t status;
}__attribute__ ((aligned (4), packed)) sunxi_uart; 




//fifo_ctl bitfields
#define SUNXI_UART_TX_RESET    (1 << 2)
#define SUNXI_UART_RX_RESET    (1 << 1)
#define SUNXI_UART_FIFO_ENABLE (1 << 0)

//line_ctl bitfields
#define SUNXI_UART_DLAB        (1 << 7)
#define SUNXI_UART_ASCII       (2 << 0)

//modem_status bitfields 
#define SUNXI_UART_RTS         (1 << 1)
#define SUNXI_UART_DTR         (1 << 0)

//line_status bitfields
#define SUNXI_UART_TXHR_EMPTY  (1 << 5)
#define SUNXI_UART_DATA_READY  (1 << 0)

//status bitfields
#define SUNXI_UART_RX_FULL     (1 << 4)
#define SUNXI_UART_RX_NEMPTY   (1 << 3)
#define SUNXI_UART_TX_EMPTY    (1 << 2)
#define SUNXI_UART_TX_NFULL    (1 << 1)
#define SUNXI_UART_BUSY        (1 << 0)


void sunxi_uart_init(sunxi_uart *);

void sunxi_uart_putc(sunxi_uart *, char);

char sunxi_uart_getc(sunxi_uart *);

#endif
