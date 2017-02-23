#include "thread_state.h"
#include "registers.h"
#include "kernel/thread.h"
#include "kernel/bb_alloc.h"
#include "kernel/malloc.h"

thread_t *init_thread;

thread_t *active_thread;

slab      thread_cache;


volatile void *active_switch_stack;


void thread_init() {
	slab_create(&thread_cache, sizeof(thread_t), page_alloc(1));

	init_thread           = slab_alloc(&thread_cache);

	active_thread         = init_thread;
	active_switch_stack   = init_thread->stack;
	init_thread->status   = THREAD_SCHEDULED;
	init_thread->user     = 0;
	init_thread->parent   = 0;
	init_thread->children = 0;
	init_thread->next     = 0;
}


void thread_exit(int ret) {
	active_thread->status = THREAD_ZOMBIE;
	active_thread->ret    = ret;
	while(1);
}



thread_t *thread_create(int (*func)(void)) {
	thread_t *new_thread = slab_alloc(&thread_cache);

	if(new_thread == 0) {
		return 0;
	}

	new_thread->parent   = active_thread;
	new_thread->next     = 0;
	new_thread->children = 0;


	new_thread->stack    = page_alloc(1);

	if(new_thread->stack == 0) {
		return 0;
	}

	new_thread->stack += (DEFAULT_STACK_SIZE - THREAD_STATE_SIZE);

	new_thread->user   = 0;

	new_thread->status = THREAD_SCHEDULED;


	*(addr_t *) (new_thread->stack + THREAD_ELR_OFFSET) = (addr_t) func;

	*(addr_t *) (new_thread->stack + THREAD_PSR_OFFSET) = THREAD_SYS_PSR;

	*(addr_t *) (new_thread->stack + THREAD_LR_OFFSET)  = (addr_t) &thread_exit;


	if(active_thread->children == 0) {
		active_thread->children = new_thread;
		return new_thread;
	} else {
		for(thread_t *i = active_thread->children; ; i = i->next) {
			if(i->next == 0) {
				i->next = new_thread;
				return new_thread;
			}
		}
	}

	return 0;
}

//Swap the stack pointers to switch into the next thread when state is reloaded.
//Updates user/kernel flags in the current thread_t appropriately;
//returns the mode of the thread_t we're switching to.
int thread_stack_switch(int current_mode) {
	thread_t *it;
	active_thread->stack = active_switch_stack;

	//active_thread->user = current_mode;

	//Round-robin cycle over the thread table, 
	//After this search, *active_thread points to the *next* thread to execute
	it = active_thread->children;
	while(it != 0) {
		if(it->status == THREAD_SCHEDULED) {
			active_thread = it;
			break;
		} else {
			it = it->next;
		}
	}

	if(it == 0) {
		it = active_thread->next;
		while(it != 0) {
			if(it->status == THREAD_SCHEDULED) {
				active_thread = it;
				break;
			} else {
				it = it->next;
			}
		}
	}

	if(it == 0) {
		it = active_thread->parent;
		while(it != 0) {
			if(it->status == THREAD_SCHEDULED) {
				active_thread = it;
				break;
			} else {
				it = it->next;
			}
		}
	}


	if(it == 0) {
		active_thread = init_thread;
	}

	active_switch_stack = active_thread->stack;

	return active_thread->user;
}


int thread_wait(thread_t *thread) {
	if(thread == 0)
		return 0;

	while(thread->status != THREAD_ZOMBIE); 

	return thread->ret;
}


void thread_join() {
	thread_t *thread = active_thread->children;

	if(thread == 0)
		return;

	while(1) {
		thread = active_thread->children;

		while(thread->next != 0) {
			thread = thread->next;

			if(thread->status != THREAD_ZOMBIE) {
				break;
			}
		}
	}

}


void print_thread_table() {
	for(thread_t *i = init_thread; ; i = i->next) {
		put_addr(i);
		puts(" : ");
		put_addr((void *)i->stack);
		puts("\n");

		if(i->children != 0) {
			for(thread_t *j = i->children; ; j = j->next) {
				puts("	");
				put_addr(j);
				puts(" : ");
				put_addr((void *)j->stack);
				puts("\n");

				if(j->next == 0)
					break;
			}
		}

		if(i->next == 0) 
			return;
	}

	
}
