#include <stdint.h>
#include "platform.h"
#include "kernel/console.h"
#include "zynq_uart.h"

void zynq_uart_irq_enable(zynq_uart *dev) {
	dev->irq_dis = 0xFFFF;
	dev->rx_fifo_trig_lvl = 1;
	dev->irq_en  =  RX_FIFO_TRIG;
	dev->channel_irq_status = 0xFFFF;
	dev->channel_irq_status = 0x0;
}

void zynq_uart_putc(zynq_uart *dev, char c) {
	while(!(dev->channel_status & TX_FIFO_EMPTY))
		;
	dev->tx_rx_fifo = c;
}


char zynq_uart_getc(zynq_uart *dev) {
	while(!(dev->channel_status & RX_FIFO_TRIG))
		irq_wait();


	return (char)(dev->tx_rx_fifo);
}


void zynq_uart_isr(zynq_uart *dev) {
	dev->irq_dis = RX_FIFO_TRIG;

	while(dev->channel_irq_status & RX_FIFO_TRIG) {
		dev->channel_irq_status = dev->channel_irq_status;
	}

	dev->irq_en = RX_FIFO_TRIG;
}



void putc(char c) {
#ifdef UART_EOL_CR_LF
	if(c == '\n') {
		zynq_uart_putc(BOOT_CON, '\r');
		zynq_uart_putc(BOOT_CON, '\n');
	} else {
		zynq_uart_putc(BOOT_CON, c);
	}
#else
	zynq_uart_putc(BOOT_CON, c);
#endif
}

char getc() {
	char c;
	c = zynq_uart_getc(BOOT_CON);

	return c;
}
