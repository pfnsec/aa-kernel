#ifndef ARCH_H
#define ARCH_H
#include <stdint.h>

extern uint64_t interrupt_vector_table[];

void arch_init();

#endif
