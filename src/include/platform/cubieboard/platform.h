#ifndef PLATFORM_H
#define PLATFORM_H
#include <stdint.h>

extern uint32_t *interrupt_vector_table;
extern uint32_t _seg_data;

void platform_init();

#define UART0 (sunxi_uart *)(0x01C28000)
#define UART1 (sunxi_uart *)(0x01C28400)


#ifndef BOOT_CON
#define BOOT_CON UART0
#endif


#define MEM_BEGIN &_seg_data
#define MEM_END (MEM_BEGIN + 0x04000000)

#endif
