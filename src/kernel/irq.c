#include "registers.h"
#include "kernel/irq.h"
#include "kernel/malloc.h"
#include "kernel/console.h"

irq_handler *bsp_handler;

int dummy_handler() {
	putc('!');
	return 1;
}

void irq_init() {
	bsp_handler = malloc(sizeof(irq_handler));

	bsp_handler->handler = 0;
	bsp_handler->asm_handler = 0;
	bsp_handler->irq_bitmask = 0;

}

void irq_register(void (*handler)(void), void (*asm_handler)(void), addr_t irq_bitmask) {
	if(handler == 0 || irq_bitmask == 0)
		return;

	irq_handler *ih = bsp_handler;
	
	do {
		if(ih->next == 0)
			break;

		ih = ih->next;
	} while(ih != 0);


	ih->next = malloc(sizeof(irq_handler));

	ih->handler     = handler;

	if(asm_handler == 0)
		ih->asm_handler = irq_return;
	else
		ih->asm_handler = asm_handler;

	ih->irq_bitmask = irq_bitmask;
}


void (*irq_top_handler(void))() {
	addr_t status = pic_irq_status();

	irq_handler *ih = bsp_handler;

	do {
		if(status & ih->irq_bitmask) {
			ih->handler();
			return ih->asm_handler;
		}

		ih = ih->next;
	} while(ih != 0);

	return &irq_return;
}
