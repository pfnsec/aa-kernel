#include <stdint.h>
#include "platform.h"
#include "uart.h"


void sunxi_uart_init(sunxi_uart *dev) {

	//while(!(dev->status & SUNXI_UART_BUSY));
	dev->line_ctl  = (SUNXI_UART_DLAB);
	dev->div_low   = 0x1; //Baud rate of 115200
	dev->div_hi    = 0x0; //Baud rate of 115200
	dev->line_ctl &= ~(SUNXI_UART_DLAB);
	dev->line_ctl  |= SUNXI_UART_ASCII;

	dev->modem_ctl |= (SUNXI_UART_RTS | SUNXI_UART_DTR);

//	dev->fifo_ctl = (SUNXI_UART_TX_RESET | SUNXI_UART_RX_RESET);
	dev->fifo_ctl = (SUNXI_UART_TX_RESET | SUNXI_UART_RX_RESET | SUNXI_UART_FIFO_ENABLE);
//	dev->fifo_ctl = (SUNXI_UART_FIFO_ENABLE);
}

void sunxi_uart_putc(sunxi_uart *dev, char c) {
	//Spin until there is space in the TX fifo
//	while(!(*(uint32_t *)(dev + 0x7c) & SUNXI_UART_TX_NFULL));

	//Qemu doesn't support the Allwinner A10 UART - only a generic 16550!
	//This is a hack until I can test on real hardware.
	while(!(dev->line_status & SUNXI_UART_TXHR_EMPTY));

	dev->trx_buf = (uint32_t)c;
}

char sunxi_uart_getc(sunxi_uart *dev) {
	//Spin until there is data in the RX fifo
//	while(!(dev->status & SUNXI_UART_RX_NEMPTY));
	
	//Qemu doesn't support the Allwinner A10 UART - only a generic 16550!
	//This is a hack until I can test on real hardware.
	while(!(dev->line_status & SUNXI_UART_DATA_READY));

	return (char)(dev->trx_buf);
}

void putc(char c) {
	sunxi_uart_putc(BOOT_CON, c);
}

char getc() {
	return sunxi_uart_getc(BOOT_CON);
}


