#include "config.h"
#include "kernel/console.h"
#include "kernel/malloc.h"
#include "kernel/thread.h"

static thread_t init_thread;

#define NULL 0

//this will obviously need to be per-cpu if we ever implement multithreading
thread_t *current_thread;

void init_thread_table() {
	current_thread = &init_thread;
	current_thread->parent = 0;
	current_thread->child = 0;
	current_thread->next = 0;
	current_thread->state = malloc(sizeof(thread_state_t));
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

void print_field(char *prefix, uint32_t field, int nspaces) {
	int i;
	for(i = 0; i < nspaces; i++)
		puts("  ");

	puts(prefix);
	puthex_32(field);
	putc('\n');
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
}
