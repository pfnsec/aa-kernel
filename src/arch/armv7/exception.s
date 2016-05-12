.section .ivt
.global interrupt_vector_table
interrupt_vector_table:
	b .             	// Reset
	b .             	// Undefined Instruction
	ldr pc, _swi_dispatch   // SWI instruction
	b .             	// Prefetch abort
	b .             	// Data abort
	b .             	// Data abort
	ldr pc, _irq_dispatch   // IRQ
	b .             	// FIQ

_swi_dispatch: .word swi_dispatch
_irq_dispatch: .word irq_dispatch


.section .text

/*
 * saved_lr and saved_spsr are variables that store lr and spsr across processor modes,
 * allowing for inter-mode state save/load.
 */


.global swi_dispatch
swi_dispatch:
	bx lr


.global irq_dispatch
.global irq_return
irq_dispatch:
	sub lr, lr, #4

	push {lr}
	push {r0-r12}


	mov r0, r14
	mrs r1, spsr

	str r0, saved_elr
	str r1, saved_spsr

	bl irq_top_handler

	mov lr, r0

	pop  {r0-r12}

	bx lr

irq_return:

	pop  {lr}

	movs pc, lr



.global task_switch
task_switch:
kernel_state_save:
	pop {lr}

	cpsid ai, #19 //Supervisor mode, interrupts disabled

	stmdb sp!, {r0-r12}

	stmdb sp!, {r14}

	ldr r0, saved_elr
	ldr r1, saved_spsr

	stmdb sp!,{r0-r1}

	ldr r0, =load_save_stack
	mov r1, sp
	str r1, [r0] 

	mov r0, #0  //Switching from Kernel Mode

	b state_load

state_load:
	bl thread_stack_switch

	teq r0, #0
	beq kernel_state_load


kernel_state_load:
	cpsid ai, #19
	ldr r0, =load_save_stack
	ldr r1, [r0] 
	mov sp, r1

	ldmia sp!,{r0-r1}

	str r0, saved_elr
	str r1, saved_spsr

	ldmia sp!,{r14}

	ldmia sp!,{r0-r12}

	cpsid ai, #18 //IRQ mode, interrupts disabled

	push {r0, r1}

	ldr r0, saved_elr
	ldr r1, saved_spsr

	mov r14, r0
	msr spsr, r1

	pop  {r0, r1}

	clrex

	movs pc, lr


/*
 * Note: 
 *  - This must only be written by the top level SWI/IRQ/FIQ handler.
 *  - It must only be read by routines invoked by these handlers.
 *  - In addition, it must be written and read before IRQs or FIQs are re-enabled. 
 *
 * Storing this data allows us to access otherwise undefined/banked registers
 * after switching mode (I.E. system/supervisor mode, for user/kernel threads respectively)
 * to save the rest of the state to the relevant stack.
*/


saved_spsr: .word 0
saved_elr:  .word 0



.global yield
yield:
	push {lr}
	swi #10
	pop {lr}
	bx lr

.global irq_enable
.global irq_disable

irq_enable:
	push {r0}
	mrs r0, cpsr
	bic r0, r0, #(1 << 7)
	msr cpsr, r0
	pop {r0}
	bx lr

irq_disable:
	push {r0}
	mrs r0, cpsr
	orr r0, r0, #(1 << 7)
	msr cpsr, r0
	pop {r0}
	bx lr

.global irq_wait
irq_wait:
	wfi
	bx lr
