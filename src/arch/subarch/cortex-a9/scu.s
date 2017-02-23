.section .text
.global scu_init
scu_init:
//	//Read ACTLR
//	mrc p15, 0, r0, c1, c0, 1


	mov r0, #((1 << 6) | 1)

	//Write ACTLR
	mcr p15, 0, r0, c1, c0, 1
	
	bx lr
