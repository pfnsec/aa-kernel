#include <stdint.h>
#include "config.h"
#include "platform.h"

#include "serial/pl011.h"

void pl011_putc(pl011_reg *dev, char c) {
	//spin until the FIFO has room
	while(dev->flags & TX_FIFO_FULL);

	dev->data = c;
}

char pl011_getc(pl011_reg *dev) {
	//spin until the FIFO receives data
	while(dev->flags & RX_FIFO_EMPTY);

	return dev->data;
}

void putc(char c) {
	pl011_putc(BOOT_CON, c);
}
