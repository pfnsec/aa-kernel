.section .text

.global smp_entry
smp_entry:
	cpsid i, #19  //Supervisor mode
	ldr sp, [r0]
	cps #18  //Enter IRQ Mode
	ldr sp, [r1]
	cps #19  //Re-enter Supervisor Mode

	mov r0, #0
	mcr p15, 0, r0, c12, c0, 0
	mcr p15, 0, r0, c12, c0, 1

