.section .init
.global init_stack
.global irq_stack

//Entry point for lead processor
.global _start
_start:
	cpsid i, #19  //Supervisor mode
	ldr sp, =init_stack
	cps #18  //Enter IRQ Mode
	ldr sp, =irq_stack
	cps #19  //Re-enter Supervisor Mode

	mov r0, #0
	mcr p15, 0, r0, c12, c0, 0
	mcr p15, 0, r0, c12, c0, 1
//	mrc p15, 0, r0, c1, c1, 0 
//	and r0, r0, #~(1 << 1)
//	mcr p15, 0, r0, c1, c1, 0 

	bl init 

halt:
	b halt


.global smp_init_stack
smp_init_stack: .word 0

.global smp_irq_stack
smp_irq_stack:  .word 0

//Entry point for non-lead processors
.global _smp_start
_smp_start:
	

	b halt
