#include "config.h"
#include "kernel/console.h"
#include "kernel/thread.h"
#include "kernel/sched.h"

void kmain() {
	puts("kmain()\n");
	schedule_thread(create_thread(current_thread));
	schedule_thread(create_thread(current_thread));
	schedule_thread(create_thread(current_thread));
	schedule_thread(create_thread(current_thread));
	schedule_thread(create_thread(current_thread));
	schedule_thread(create_thread(current_thread));

	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");
	puthex_32((uint32_t)next_thread(pri_table));
	puts("\n");

}
