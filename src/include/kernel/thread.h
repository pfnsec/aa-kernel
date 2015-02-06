#ifndef THREAD_H
#define THREAD_H
#include "config.h"
#include <stdint.h>
#include "thread_state.h"
#include "kernel/console.h"


#define DEFAULT_STACK_SIZE 4096


typedef struct thread_t {
	thread_state_t  *state;
	struct thread_t *parent;
	struct thread_t *child;
	struct thread_t *next;
	int ret_code; //return code of thread_func()
} thread_t;

extern thread_t *current_thread;

void init_thread_table();

thread_t *create_thread(thread_t *parent);

void print_thread_table();


#endif
