#ifndef IRQ_H
#define IRQ_H
#include <stdint.h>
#include "registers.h"



typedef struct irq_handler {
	void   (*handler)(volatile void *);
	void   (*asm_handler)(void);
	volatile void  *dev;
	unsigned int nirq;
	struct   irq_handler *next;
} irq_handler;

void irq_init();

void irq_register(void (*handler)(volatile void *), void (*asm_handler)(void), volatile void *dev, unsigned int nirq);

void irq_unregister(unsigned int nirq);

void irq_wait();

void *irq_handle(unsigned int nirq);

void irq_enable();

void irq_disable();

void pic_irq_enable (unsigned int nirq);

void pic_irq_disable(unsigned int nirq);

int  pic_irq_pending(unsigned int nirq);

void  pic_irq_clear(unsigned int nirq);

void  pic_irq_eoi(unsigned int nirq);

extern void irq_return(void);


#endif
