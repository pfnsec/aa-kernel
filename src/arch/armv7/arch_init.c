#include <stdint.h>
#include "arch.h"

void arch_init() {
	for(int i = 0; i < 16; i++) {
		//Copy interrupt vector table
		//*(uint32_t *)(i * 4) = *(uint32_t *)(interrupt_vector_table + (i* 4));
		((uint32_t *)(0))[i] = interrupt_vector_table[i];
	} 
}
