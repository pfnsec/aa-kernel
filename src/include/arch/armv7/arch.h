#ifndef ARCH_H
#define ARCH_H
#include <stdint.h>
#include "cp15.h"

extern uint32_t interrupt_vector_table[];

void arch_init();

void subarch_init();

void arch_timer_init();

void arch_timer_isr();



#define cpu_read_cp15(op1, crn, crm, op2, a) asm volatile ("mrc p15, %0, %1, %2, %3, %4" : : (op1), "r"(a), (crn), (crm), (op2) : )

#endif
