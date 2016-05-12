#ifndef PLATFORM_H
#define PLATFORM_H
#include "kernel/framebuffer.h"

extern uint32_t _seg_data;

void platform_init();


extern fb_desc boot_fb_desc;


#define UART0 (pl011 *)(0x16000000)
#define UART1 (pl011 *)(0x17000000)


#ifndef BOOT_CON
#define BOOT_CON UART0
#endif


#define MEM_BEGIN &_seg_data
#define MEM_END  (uint32_t *)0x1008000

#endif
