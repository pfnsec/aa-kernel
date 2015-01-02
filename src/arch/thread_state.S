#include "config.h"


#if ARCH == ARMv7
//thread_state_t * of the currently running thread
.global current_thread_state

.global load_thread_state
load_thread_state_old:
	ldr r0, =current_thread_state
	ldr r0, [r0]
	ldmib r0!,{r1-r12}

	ldr r0, =current_thread_state
	ldr r0, [r0]
	ldr sp, [r0,#52]
	ldr lr, [r0,#56]

	ldr r0, [r0]
	
	bx lr


.global save_thread_state
save_thread_state_old:
	push {r0}

	ldr r0, =current_thread_state
	ldr r0, [r0]
	stmib r0!,{r1-r12}

	ldr r1, =current_thread_state
	ldr r1, [r1]

//	push {lr}
//	mov lr, #255
//	str lr, [r1,#56]
//:	pop {lr}

	pop {r0}
	str r0, [r1]

	str sp, [r1,#52]	

	bx lr


load_thread_state:
//	str r0,[sp,#-4]
	ldr r0, =current_thread_state
	ldr r0, [r0]

	push {lr}
	bl puthex_32
	pop {lr}


	ldr r1, [r0,#60]
	msr cpsr, r1

	add r0, r0, #4
	ldmia r0!,{r1-r12}

	ldr r0, =current_thread_state
	ldr r0, [r0]

	ldr sp, [r0,#52]
	ldr lr, [r0,#56]


	ldr r0,[r0]
	bx lr


save_thread_state:
	str r0,[sp,#-4]
	ldr r0, =current_thread_state
	ldr r0, [r0]
	add r0, r0, #4
	stmia r0!,{r1-r12}

	ldr r0, =current_thread_state
	ldr r0, [r0]

	str sp, [r0,#52]	

	str lr, [r0,#56]	

	mrs r1, cpsr
	str r1, [r0,#60]	

	ldr r1,[sp,#-4]
	str r1,[r0]
	mov r0, r1
	bx lr

#endif
/*
.global load_thread_state
load_thread_state:
	bx lr

.global save_thread_state
save_thread_state:
	bx lr
*/
