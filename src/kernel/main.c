#include "config.h"
#include "kernel/console.h"
#include "kernel/thread.h"
#include "kernel/sched.h"


thread_t *test1;
thread_t *test2;

void test1_thread() {
	while(1) {
		puts("1\n");
//		print_thread_state(test1);
		switch_to_thread(test2);
	}
}

void test2_thread() {
	while(1) {
		puts("2\n");
//		print_thread_state(test2);
		switch_to_thread(test1);
	}
}

void kmain() {
	test1 = create_thread(current_thread);
	test2 = create_thread(current_thread);
	create_thread_state(test1, test1_thread, 0, 0);
	create_thread_state(test2, test2_thread, 0, 0);

	while(1) {
//		print_thread_state(current_thread);
		switch_to_thread(test1);
		while(1);
	}
}
