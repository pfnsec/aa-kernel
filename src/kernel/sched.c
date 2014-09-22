#include "config.h"
#include "kernel/console.h"
#include "kernel/malloc.h"
#include "kernel/thread.h"
#include "kernel/sched.h"

sched_table *pri_table;

void init_sched() {
	pri_table = malloc(sizeof(sched_table));
	pri_table->top = malloc(sizeof(sched_entry));
	pri_table->current = pri_table->bot = pri_table->top;
	pri_table->top->thread = current_thread;
}

void schedule_thread(thread_t *thread) {
	sched_entry *new;

	new = malloc(sizeof(sched_entry));

	new->thread = thread;
	new->next = 0;
	pri_table->bot->next = new;
	pri_table->bot = new;
}

thread_t *next_thread(sched_table *sched) {
	if(sched->current->next == 0) {
		sched->current = sched->top;
	} else {
		sched->current = sched->current->next;
	}
	return sched->current->thread;
}
