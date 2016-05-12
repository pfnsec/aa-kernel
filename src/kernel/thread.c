#include "thread_state.h"
#include "registers.h"
#include "kernel/thread.h"
#include "kernel/malloc.h"

thread_t init_thread;

thread_t *current_thread;


volatile addr_t load_save_stack;


void thread_init() {
	current_thread       = &init_thread;
	load_save_stack      = init_thread.stack;
	init_thread.status   = THREAD_SCHEDULED;
	init_thread.user     = 0;
	init_thread.parent   = 0;
	init_thread.children = 0;
	init_thread.next     = 0;
}


void thread_exit(int ret) {
	current_thread->status      = THREAD_ZOMBIE;
	current_thread->ret = ret;
	while(1);
}



thread_t *thread_create(int (*func)(void)) {
	thread_t *new_thread = malloc(sizeof (thread_t));

	if(new_thread == 0) {
		return 0;
	}

	new_thread->parent   = current_thread;
	new_thread->next     = 0;
	new_thread->children = 0;


	new_thread->stack    = (addr_t) (malloc(DEFAULT_STACK_SIZE));

	if(new_thread->stack == 0) {
		return 0;
	}

	new_thread->stack += (DEFAULT_STACK_SIZE - THREAD_STATE_SIZE);

	new_thread->user = 0;

	new_thread->status = THREAD_SCHEDULED;


	*(addr_t *) (new_thread->stack + THREAD_ELR_OFFSET) = (addr_t) func;
	*(addr_t *) (new_thread->stack + THREAD_PSR_OFFSET) = THREAD_SYS_PSR;

	*(addr_t *) (new_thread->stack + THREAD_LR_OFFSET)  = (addr_t) &thread_exit;


	if(current_thread->children == 0) {
		current_thread->children = new_thread;
		return new_thread;
	} else {
		for(thread_t *i = current_thread->children; ; i = i->next) {
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
	current_thread->stack = load_save_stack;

	//current_thread->user = current_mode;

//	put_addr(current_thread->stack);

	//Round-robin cycle over the thread table, 
	//After this search, *current_thread points to the *next* thread to execute
	it = current_thread->children;
	while(it != 0) {
		if(it->status == THREAD_SCHEDULED) {
			current_thread = it;
			break;
		} else {
			it = it->next;
		}
	}

	if(it == 0) {
		it = current_thread->next;
		while(it != 0) {
			if(it->status == THREAD_SCHEDULED) {
				current_thread = it;
				break;
			} else {
				it = it->next;
			}
		}
	}

	if(it == 0) {
		it = current_thread->parent;
		while(it != 0) {
			if(it->status == THREAD_SCHEDULED) {
				current_thread = it;
				break;
			} else {
				it = it->next;
			}
		}
	}


	if(it == 0) {
		current_thread = &init_thread;
	}

//	put_addr(current_thread->stack);
//	puts("\n");
/*
	puts(" -> ");

	put_addr(current_thread->stack);

	puts("\n");

	puts("stack[0..5]:\n");

	for(int i = 0; i < 5; i++) {
		puts("	");
		put_addr(*(addr_t *)(current_thread->stack + i * 4));
		puts("\n");
	}
*/

	load_save_stack = current_thread->stack;

	return current_thread->user;
}


int thread_wait(thread_t *thread) {
	if(thread == 0)
		return 0;

	while(thread->status != THREAD_ZOMBIE); 

	return thread->ret;
}


void thread_join() {
	thread_t *thread = current_thread->children;

	if(thread == 0)
		return;

	while(1) {
		thread = current_thread->children;

		while(thread->next != 0) {
			thread = thread->next;

			if(thread->status != THREAD_ZOMBIE) {
				break;
			}
		}
	}

}


void print_thread_table() {
	for(thread_t *i = &init_thread; ; i = i->next) {
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
