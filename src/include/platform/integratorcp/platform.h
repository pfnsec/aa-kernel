#ifndef PLATFORM_H
#define PLATFORM_H
#include <stdint.h>
#include "kernel/framebuffer.h"
#include "drivers/serial/pl011.h"
#include "drivers/framebuffer/pl110.h"
#include "pic.h"
#include "icp_timer.h"

extern uint32_t _seg_data;

void platform_init();


extern fb_desc boot_fb_desc;


#define MEM_BEGIN &_seg_data
#define MEM_END (MEM_BEGIN + 0x04000000)


#define TIMER0 (icp_timer *)(0x13000000)

#define PIC0   (icp_pic *)  (0x14000000)

#define UART0  (pl011 *)    (0x16000000)
#define UART1  (pl011 *)    (0x17000000)

#define FB0    (pl110 *)    (0xc0000000)


#define BOOT_CON UART0
#define BOOT_FB  FB0


#define BOOT_CON_IRQ    PIC_IRQ_UART0
#define TIMER0_IRQ      PIC_IRQ_TIMER0


#define TASK_SWITCH_TIMER TIMER0
#define TASK_SWITCH_IRQ TIMER0_IRQ


#endif
