#include "registers.h"
#include "kernel/irq.h"
#include "kernel/malloc.h"
#include "kernel/bb_alloc.h"
#include "kernel/console.h"

irq_handler *bsp_handler;

slab *irq_handler_cache;

int dummy_handler() {
	putc('!');
	return 1;
}

void irq_init() {
	bsp_handler = malloc(sizeof(irq_handler));

	if(bsp_handler == 0) {
		puts("irq_init(): Failed to allocate bsp_handler!\n");
		return;
	}

	bsp_handler->handler = 0;
	bsp_handler->asm_handler = 0;
	bsp_handler->dev     = 0;
	bsp_handler->nirq    = 0;
	bsp_handler->next    = 0;

}

void irq_register(void (*handler)(volatile void *), 
                  void (*asm_handler)(void), 
                  volatile void *dev, 
                  unsigned int nirq) 
{
//	printf("irq_register(%w, %w, %w, %w);\n", handler, asm_handler, dev, nirq);
	if(handler == 0 || nirq == 0 || bsp_handler == 0)
		return;

	irq_handler *ih = bsp_handler;
	
	while(ih->next != 0) {
		ih = ih->next;
	}


	ih->next = malloc(sizeof(irq_handler));

	if(ih->next == 0) {
		printf("irq_register(nirq = %w): Failed to register an irq handler!\n", nirq);
		return;
	}


	ih = ih->next;


	ih->next = 0;

	ih->handler = handler;

	if(asm_handler == 0)
		ih->asm_handler = irq_return;
	else
		ih->asm_handler = asm_handler;

	ih->dev  = dev;

	ih->nirq = nirq;

	pic_irq_enable(nirq);
}


void *irq_handle(unsigned int n) {

	irq_handler *ih = bsp_handler;


	do {
		if(ih->nirq == n) {
			ih->handler(ih->dev);
			pic_irq_clear(n);
			pic_irq_eoi(n);

			return ih->asm_handler;
		}

		ih = ih->next;
	} while(ih != 0);

	printf("Unhandled: nIRQ_%h\n", n);


	return &irq_return;
}
