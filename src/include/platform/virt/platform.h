#ifndef PLATFORM_H
#define PLATFORM_H
#include <stdint.h>

extern uint64_t _seg_data;

void platform_init();


#define PERIPH_BASE      (0x08000000)


#define UART0   (pl011 *)(0x09000000)

#define GIC_DIST (gicv2_cpu *)(PERIPH_BASE)
#define GIC_CPU  (gicv2_cpu *)(PERIPH_BASE + 0x10000)


#ifndef BOOT_CON
#define BOOT_CON UART0
#endif

#define MEM_BEGIN &_seg_data
#define MEM_END (MEM_BEGIN + 0x04111000)

#endif
