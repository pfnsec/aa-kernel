#ifndef THREAD_STATE_H
#define THREAD_STATE_H


#define THREAD_STATE_SIZE 16*4

#define THREAD_ELR_OFFSET  0*4
#define THREAD_PSR_OFFSET  1*4
#define THREAD_LR_OFFSET   2*4


//CPSR: Supervisor mode, with IRQ, FIQ, and Imprecise Abort disabled
//#define THREAD_SYS_PSR    (0x13) | (0b111 << 6)
#define THREAD_SYS_PSR    (0x13)




#endif
