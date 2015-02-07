.text
#include "config.h"

#if ARCH == armv7
interrupt_vector_table:
	b . // Reset
	b . 
	b _swi_dispatch // SWI instruction
	b . 
	b .
	b .
	b .
	b .

_stack_bot:
.global _stack_bot

_stack:
.global _stack
.skip 0x1000 // Reserve 4k stack in the BSS

_start:
	.global _start
	ldr sp, =_stack+0x1000 // Set up the stack
	bl init // Jump to the main function
1: 
	b 1b // Halt

_swi_dispatch:
	bl swi_handler
	pop {lr}
	bx lr


.global interrupt_call
interrupt_call:
        push {lr}
        swi 0

#endif
