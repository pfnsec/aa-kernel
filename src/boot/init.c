#include "arch.h"
#include "platform.h"
#include "kernel/main.h"
#include "kernel/malloc.h"
#include "kernel/bb_alloc.h"
#include "kernel/thread.h"
#include "kernel/irq.h"

void init() {
	arch_init();

	subarch_init();

	bb_alloc_init();

	alloc_init();

	thread_init();

	irq_init();

	platform_init();

	irq_enable();

	block_init();

	kmain();
}
