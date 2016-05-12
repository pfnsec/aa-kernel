#include "drivers/serial/pl011.h"
#include "kernel/main.h"
#include "kernel/malloc.h"
#include "kernel/thread.h"
#include "arch.h"
#include "platform.h"

void init() {
	arch_init();
	alloc_init();
	thread_init();
	irq_init();

	platform_init();
	kmain();
}
