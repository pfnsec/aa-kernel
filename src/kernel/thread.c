#include "config.h"
#include "kernel/console.h"
#include "kernel/malloc.h"
#include "kernel/thread.h"

thread_t init_thread;

#define NULL 0

//this will obviously need to be per-cpu if we ever support SMP 
thread_t *current_thread;

void init_thread_table() {
	current_thread = &init_thread;
	current_thread->parent = 0;
	current_thread->child = 0;
	current_thread->next = 0;
	current_thread->state = malloc(sizeof(thread_state_t));

	current_thread_state = &current_thread->state->reg; //god dammit
	save_thread_state();
}

thread_t *create_thread(thread_t *parent) {
	thread_t *thread;
	thread_t *prev; //last entry in parent->child (parent->child->next == 0)

	thread = malloc(sizeof(thread_t));

	thread->state = malloc(sizeof(thread_state_t));

	thread->parent = parent;
	thread->child = NULL;

	prev = parent->child;
	if(prev == NULL) {
		parent->child = thread;
	} else {
		while(prev->next != NULL) {
			prev = prev->next;
		}
		prev->next = thread;
	}
	return thread;
}


void thread_exit() {
	puts("Exiting...\n");
	yield();
}


//initializes thread->state with registers, allocates a stack, and sets up execution to begin at thread_func
void create_thread_state(thread_t *thread, int (*thread_func(void *)), void *thread_param, uint32_t stack_size) {
	int i;
	void *stack;

	for (i = 0; i < 16; i++) {
		thread->state->reg[i] = 0;
	}	

	if(stack_size == 0) {
		stack = (void *)(malloc(DEFAULT_STACK_SIZE) + DEFAULT_STACK_SIZE);
	} else {
		stack = (void *)(malloc(stack_size) + stack_size);
	}

//	puthex_32(stack);
//	putc('\n');

	thread->state->reg[0]  = (uint32_t) thread_param;
	thread->state->reg[13] = (uint32_t) stack;
//	thread->state->reg[13] = (uint32_t) thread_exit;
	thread->state->reg[14] = (uint32_t) thread_func;
}


void switch_to_thread(thread_t *thread) {
	if(thread == 0 || thread->state == 0) {
		puts("Error: switch_to_thread was called with NULL");
		return;
	}
/*
	puts("switch_to_thread(");
	puthex_32(thread);
	puts(")\n");
*/
	save_thread_state();

	current_thread = thread;
	current_thread_state = &thread->state->reg;

	load_thread_state();
}


void print_field(char *prefix, uint32_t field, int nspaces) {
	int i;
	for(i = 0; i < nspaces; i++)
		puts("  ");

	puts(prefix);
	puthex_32(field);
	putc('\n');
}

void print_thread_state(thread_t *thread) {
	int i;

	puthex_32(thread);
	puts(": (thread->state = \n");
	puthex_32(&thread->state->reg);
	puts(")\n");

	for(i = 0; i < 16; i++) {
		putc('	');
		puthex_32(thread->state->reg[i]);
		puts("\n");
	}
}

void print_table_rec(thread_t *cur, int nspaces) {
	thread_t *child;
	print_field("Thread: ", (uint32_t)cur, nspaces);
	print_field("Parent: ", (uint32_t)cur->parent, nspaces);

	child = cur->child;
	while(child != NULL) {
		print_table_rec(child, nspaces + 1);
		child = child->next;
	}
}

void print_thread_table() {
	print_table_rec(&init_thread, 0);
	puts("Current thread:");
	puthex_32((uint32_t) current_thread);
	puts("\n");
}
