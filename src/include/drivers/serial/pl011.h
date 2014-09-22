#ifndef PL011_H
#define PL011_H
#include <stdint.h>
#include "config.h"

#define TX_FIFO_FULL  (1 << 5)
#define RX_FIFO_EMPTY (1 << 4)

typedef struct pl011_reg {
	uint32_t data;
	uint32_t error_status;
	char pad1[16];
	uint32_t flags;
	char pad2[16];
	uint32_t control;
}__attribute__ ((aligned (4), packed)) pl011_reg; 


void pl011_putc(pl011_reg *, char c);


#if PLATFORM == integratorcp

	#define UART0 (pl011_reg *)(0x16000000)
	#define UART1 (pl011_reg *)(0x17000000)

#endif
#endif
