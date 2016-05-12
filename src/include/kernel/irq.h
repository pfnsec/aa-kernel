#ifndef IRQ_H
#define IRQ_H
#include "registers.h"



typedef struct irq_handler {
	int  (*handler)(void);
	void (*asm_handler)(void);
	addr_t irq_bitmask;
	struct irq_handler *next;
} irq_handler;

void irq_init();

void irq_register(void (*handler)(void), void (*asm_handler)(void), addr_t irq_bitmask);

void irq_unregister(addr_t irq_bitmask);

void irq_wait();

void irq_enable();

void irq_disable();

void pic_irq_enable (addr_t irq_bitmask);

void pic_irq_disable(addr_t irq_bitmask);

addr_t pic_irq_status();

extern void irq_return(void);


#endif
