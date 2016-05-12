.text

_stack_bot:
.global _stack_bot

.skip 0x10000 
_stack:
.global _stack

_start:
	.global _start
	ldr x0, =_stack
	mov x29, x0 
	mov sp, x0 

	ldr x0, =vbar_interrupt_table

	msr vbar_el1, x0

	b init

_hang: 
	b _hang


.global yield
yield:
	stp x0, x30, [sp, #-16]!

	svc #10
	ldp x0, x30, [sp], #16
	ret
