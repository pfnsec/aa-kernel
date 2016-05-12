#ifndef SCHED_H
#define SCHED_H
#include "kernel/thread.h"

typedef struct sched_entry {
	thread_t *thread;
	struct sched_entry *next;
} sched_entry;

typedef struct sched_table {
	sched_entry *top;
	sched_entry *bot;
	sched_entry *current;
} sched_table;

sched_table *pri_table;

void init_sched();

void schedule_thread(thread_t *thread);

thread_t *next_thread(sched_table *sched);

void yield();

#endif
