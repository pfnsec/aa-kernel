#include "config.h"
#include "drivers/serial/pl011.h"
#include "kernel/main.h"
#include "kernel/malloc.h"
#include "kernel/thread.h"
#include "kernel/sched.h"

void init() {
	init_alloc_table();
	init_thread_table();
	init_sched();
	kmain();
}
