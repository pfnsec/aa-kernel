.section .init
.global init_stack
.global irq_stack


.global _start
_start:
	ldr sp, =init_stack

	cps #18  //Enter IRQ Mode
	ldr sp, =irq_stack
	cps #19  //Re-enter Supervisor Mode

	bl init 

halt:
	b halt

	
