.section .text
.global cpu_read_scr
.global cpu_write_scr


cpu_read_scr:
	mrc p15, 0, r0, c1, c1, 0 
	bx lr


cpu_write_scr:
	mcr p15, 0, r0, c1, c1, 0 
	bx lr
