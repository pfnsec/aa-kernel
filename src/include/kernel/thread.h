#ifndef THREAD_H
#define THREAD_H
#include <stdint.h>
#include "thread_state.h"
#include "kernel/console.h"
#include "registers.h"
#include "kernel/fs/ip_fs.h"


#define DEFAULT_STACK_SIZE 4096


#define INIT_PID_RANGE 4096


#define THREAD_SCHEDULED 0
#define THREAD_BLOCKED   1
#define THREAD_ZOMBIE    2


extern volatile addr_t load_save_stack;


typedef struct thread_t {
	int              user;
	volatile int     status;
	int              id;
	volatile int     ret;
	volatile void   *stack;
	struct thread_t *parent;
	struct thread_t *children;
	struct thread_t *next;
} thread_t;


typedef struct thread_list {
	thread_t *thread;
	struct thread_list *next;
} thread_list;


extern thread_t *current_thread;


void thread_init();

thread_t *thread_create(int (*func)(void));

thread_t *thread_id_lookup(int id);

void thread_destroy(thread_t *);

int thread_wait(thread_t *);

void thread_join();

void yield();

void print_thread_table();

extern void task_switch();


#endif
