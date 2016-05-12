#ifndef PL011_H
#define PL011_H
#include <stdint.h>
#include "platform.h"

//pl011->flags bitfields
#define TX_FIFO_FULL  (1 << 5)
#define RX_FIFO_EMPTY (1 << 4)


//pl011->control bitfields
#define PL011_CTS_EN  (1 << 15)
#define PL011_RTS_EN  (1 << 14)
#define PL011_ENABLE  (1 << 0)


//pl011->line_control bitfields
#define PL011_FIFO_EN (1 << 4)


#define PL011_IRQ_RX  (1 << 4)


typedef volatile struct pl011 {
	uint32_t data;
	uint32_t error_status;
	uint32_t pad1[4];
	uint32_t flags;
	uint32_t pad2[4];
	uint32_t line_control;
	uint32_t control;
	uint32_t irq_level;
	uint32_t irq_mask;
	uint32_t irq_raw_status;
	uint32_t irq_mask_status;
	uint32_t irq_clear;
}__attribute__ ((packed)) pl011; 


void pl011_init(pl011 *);

void pl011_putc(pl011 *, char c);

char pl011_getc(pl011 *);

void pl011_irq_handler();

#endif
