#include <stdint.h>
#include "kernel/mutex.h"
#include "kernel/irq.h"
#include "platform.h"
#include "drivers/serial/pl011.h"
#include "pic.h"


mutex pl011_mutex = 0;


void pl011_irq_clear(pl011 *dev, int n) {
	dev->irq_clear  =  n;
}


void pl011_irq_enable(pl011 *dev, int n) {
	pic_irq_disable(BOOT_CON_IRQ);
	dev->irq_clear  =  n;
//	dev->irq_mask  &= ~n;
	dev->irq_mask  |=  n;
	pic_irq_enable(BOOT_CON_IRQ);
}


void pl011_init(pl011 *dev) {
	dev->control  &= (PL011_ENABLE);

	dev->line_control  &= ~(PL011_FIFO_EN);

	dev->control  |= (PL011_ENABLE);

	pl011_irq_enable(dev, PL011_IRQ_RX);
}


void pl011_putc(pl011 *dev, char c) {
//	irq_disable();
//	mutex_lock(&pl011_mutex);
	//spin until the FIFO has room
	while((dev->flags) & TX_FIFO_FULL);

	dev->data = c;
//	mutex_unlock(&pl011_mutex);

//	irq_enable();
}


char pl011_getc(pl011 *dev) {
	//spin until the FIFO receives data
	while((dev->flags) & RX_FIFO_EMPTY);

	return dev->data;
}


void putc(char c) {
	pl011_putc(BOOT_CON, c);
}

char getc() {
	return pl011_getc(BOOT_CON);
}

void pl011_irq_handler() {
	pl011_irq_clear(BOOT_CON, PL011_IRQ_RX);
	putc(getc());
}
