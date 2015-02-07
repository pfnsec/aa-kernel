#include "config.h"
#include "kernel/console.h"
#include "kernel/malloc.h"
#include "kernel/thread.h"
#include "kernel/sched.h"

sched_table *pri_table;
//uint32_t *current_thread_state __attribute__((aligned (4)));
thread_state_t *current_thread_state;
thread_t *scheduler_thread;

int do_sched(void *);

void init_sched() {
	pri_table = malloc(sizeof(sched_table));
	pri_table->top = malloc(sizeof(sched_entry));
	pri_table->current = pri_table->bot = pri_table->top;
	pri_table->top->thread = current_thread;

	scheduler_thread = create_thread(current_thread);
	create_thread_state(scheduler_thread, do_sched, pri_table, 0);

//	schedule_thread(scheduler_thread);
}

void schedule_thread(thread_t *thread) {
	sched_entry *new;

	new = malloc(sizeof(sched_entry));

	new->thread = thread;
	new->next = 0;
	pri_table->bot->next = new;
	pri_table->bot = new;
}

//returns the next thread to run
thread_t *next_thread(sched_table *sched) {
	if(sched->current->next == 0) {
		sched->current = sched->top;
	} else {
		sched->current = sched->current->next;
	}

//	current_thread_state = &sched->current->thread->state->reg;
/*	puts("next_thread()\n");

	puthex_32(sched->current->thread);
	putc('\n');
*/
	return sched->current->thread;
}

//the 'meat' of the scheduler - this is the function passed to create scheduler_thread
int do_sched(void *table) {
	while(1) {
/*		puts("do_sched(0x");
		puthex_32(table);
		puts(")\n");
		*/
		switch_to_thread(next_thread(table));
	}
	return 0;
}

void yield() {
//	puts(".yield()\n");

//	print_thread_state(current_thread);

//	switch_to_thread(scheduler_thread);

	switch_to_thread(next_thread(pri_table));
}

void print_sched_table(sched_table *tbl) {
	sched_entry *cur;
	
	puts("Sched Table: ");
	puthex_32(tbl);
	puts("\n");

	for(cur = tbl->top; cur != 0; cur = cur->next) {
		puthex_32(cur->thread);
		putc('\n');
	}
}


void print_pri_table() {
	print_sched_table(pri_table);
}


