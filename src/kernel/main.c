#include "config.h"
#include "kernel/console.h"
#include "kernel/thread.h"
#include "kernel/sched.h"

void test_thread() {
	while(1) {
		puts("test_thread()\n");
		yield();
	}
}

void kmain() {
	thread_t *test;

	test = create_thread(current_thread);
	create_thread_state(test, test_thread, 0, 0);

	schedule_thread(test);

	while(1) {
		puts("main_thread()\n");
		yield();
	}
}
