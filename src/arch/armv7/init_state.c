#include <stdint.h>
#include "config.h"
#include "thread_state.h"
#include "kernel/console.h"
#include "kernel/malloc.h"
#include "kernel/thread.h"


void thread_exit() {
	puts("Exiting...\n");
	yield();
}


//initializes thread->state with registers, allocates a stack, and sets up execution to begin at thread_func
void create_thread_state(thread_t *thread, int (*thread_func(void *)), void *thread_param, uint32_t stack_size) {
	int i;
	uint32_t *stack;

	save_thread_state();


	for (i = 0; i < 16; i++) {
		*thread->state[i] = current_thread_state[i];
	}	


	if(stack_size == 0) {
		stack = (void *)(malloc(DEFAULT_STACK_SIZE) + DEFAULT_STACK_SIZE);
		if(stack == DEFAULT_STACK_SIZE) {
			puts("create_thread_state(): failed to allocate stack!\n");
			return;
		}
	} else {
		stack = (void *)(malloc(stack_size) + stack_size);
		if(stack == stack_size) {
			puts("create_thread_state(): failed to allocate stack!\n");
			return;
		}
	}


//	stack[-1] = thread_exit;

	*thread->state[0]  = (uint32_t) thread_param;
	*thread->state[13] = (uint32_t) stack;
//	thread->state->reg[13] = (uint32_t) thread_exit;
	*thread->state[14] = (uint32_t) thread_func;
	*thread->state[15] = get_cpsr();

}
