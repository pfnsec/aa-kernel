#include "config.h"

//target of save_thread_state() - used only to initialize new thread states
.global saved_thread_state
//thread_t->state->reg of the currently running thread (old) or the thread to run next (new)
.global current_thread_state_old
.global current_thread_state_new

.global load_thread_state

.global save_thread_state

load_thread_state:
	str r0,[sp,#-4]
	ldr r0, =current_thread_state

//	push {lr}
//	bl puthex_32
//	pop {lr}

	ldr r0, [r0]

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
	ldr r0, =saved_thread_state
	ldr r0, [r0]
	add r0, r0, #4
	stmia r0!,{r1-r12}

	ldr r0, =saved_thread_state
	ldr r0, [r0]

	str sp, [r0,#52]	

	//store lr 
	ldr r1,[sp,#12]
	str r1, [r0,#56]	
//	str lr, [r0,#56]	

	mrs r1, cpsr
	str r1, [r0,#60]	

	ldr r1,[sp,#-4]
	str r1,[r0]
	mov r0, r1
	bx lr

.global get_cpsr
get_cpsr:
	mrs r0, cpsr
	bx lr

.global do_context_switch
do_context_switch:
	str r0,[sp,#-4]
	ldr r0, =current_thread_state_old
	ldr r0, [r0]
	add r0, r0, #4
	stmia r0!,{r1-r12}

	ldr r0, =current_thread_state_old
	ldr r0, [r0]

	str sp, [r0,#52]	

	str lr, [r0,#56]	

	mrs r1, cpsr
	str r1, [r0,#60]	

	ldr r1,[sp,#-4]
	str r1,[r0]
	mov r0, r1

	ldr r0, =current_thread_state_new

	ldr r0, [r0]

	ldr r1, [r0,#60]
	msr cpsr, r1

	add r0, r0, #4
	ldmia r0!,{r1-r12}

	ldr r0, =current_thread_state_new
	ldr r0, [r0]

	ldr sp, [r0,#52]
	ldr lr, [r0,#56]


	ldr r0,[r0]
	bx lr
