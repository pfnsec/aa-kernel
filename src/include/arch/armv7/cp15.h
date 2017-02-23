#ifndef CP15_H
#define CP15_H
#include <stdint.h>

uint32_t cpu_read_scr();
void     cpu_write_scr(uint32_t);

#endif
