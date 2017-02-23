#include <stdint.h>
#include "arch.h"
#include "kernel/console.h"

void arch_init() {
	for(int i = 0; i < 16; i++) {
		//Copy interrupt vector table
		((volatile uint32_t *)(0x00000000))[i] = interrupt_vector_table[i];
	} 
}

void arch_smp_init() {
}

void dump_vectors() {
	puts("Vector Table (0x00000000):\n");
	for(int i = 0; i < 16; i++) {
		puthex_32(((uint32_t *)(0))[i]);
		putc('\n');
	} 

	puts("Vector Table (0xFFFF0000):\n");
	for(int i = 0; i < 16; i++) {
		puthex_32(((uint32_t *)(0xFFFF0000))[i]);
		putc('\n');
	} 
}

void dump_scr() {

	puts("SCR: ");
	puthex_32(cpu_read_scr());
	putc('\n');
}

void raise() {
}
