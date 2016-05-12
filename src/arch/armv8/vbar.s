.section .text

.align 11
.global vbar_interrupt_table
vbar_interrupt_table:

//Synchronous exceptions, E.G. svc
.org (vbar_interrupt_table + 0x200)
vbar_sync_spx:
	b svc_handler

//IRQ 
.org (vbar_interrupt_table + 0x280)
vbar_irq_spx:
	b svc_handler


//End of VBAR
.org (vbar_interrupt_table + 0x800)

svc_handler:

	stp x0,  x1,  [sp, #-16]!
	stp x2,  x3,  [sp, #-16]!
	stp x4,  x5,  [sp, #-16]!
	stp x6,  x7,  [sp, #-16]!
	stp x8,  x9,  [sp, #-16]!
	stp x10, x11, [sp, #-16]!
	stp x12, x13, [sp, #-16]!
	stp x14, x15, [sp, #-16]!
	stp x16, x17, [sp, #-16]!
	stp x18, x19, [sp, #-16]!
	stp x20, x21, [sp, #-16]!
	stp x22, x23, [sp, #-16]!
	stp x24, x25, [sp, #-16]!
	stp x26, x27, [sp, #-16]!
	stp x28, x29, [sp, #-16]!
	stp x30, x0,  [sp, #-16]!

	mrs x0, elr_el1
	mrs x1, spsr_el1


	stp x0, x1,   [sp, #-16]!

//	sub sp, sp, #16


//	ldr x0, =load_save_stack
//	mov x1, sp
//	str x1, [x0]

	adr x0, load_save_stack
	mov x1, sp
	str x1, [x0]

	bl thread_stack_switch

//	ldr x0, =load_save_stack
//	ldr x1, [x0]

	adr x0, load_save_stack
	ldr x1, [x0]
	mov sp, x1


//	add sp, sp, #16

	ldp x0, x1,   [sp], #16


	msr elr_el1,  x0
	msr spsr_el1, x1

	ldp x30, x0,  [sp], #16
	ldp x28, x29, [sp], #16
	ldp x26, x27, [sp], #16
	ldp x24, x25, [sp], #16
	ldp x22, x23, [sp], #16
	ldp x20, x21, [sp], #16
	ldp x18, x19, [sp], #16
	ldp x16, x17, [sp], #16
	ldp x14, x15, [sp], #16
	ldp x12, x13, [sp], #16
	ldp x10, x11, [sp], #16
	ldp x8,  x9,  [sp], #16
	ldp x6,  x7,  [sp], #16
	ldp x4,  x5,  [sp], #16
	ldp x2,  x3,  [sp], #16
	ldp x0,  x1,  [sp], #16

	eret


.global irq_enable
irq_enable:
	stp x0, x1, [sp, #-16]!
	mrs x0, daif
	bic x0, x0, #(1 << 7)
	msr daif, x0
	ldp x0, x1, [sp], #16
	ret

.global irq_disable
irq_disable:
	stp x0, x1, [sp, #-16]!
	mrs x0, daif
	orr x0, x0, #(1 << 7)
	msr daif, x0
	ldp x0, x1, [sp], #16
	ret
