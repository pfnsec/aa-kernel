#ifndef PLATFORM_H
#define PLATFORM_H
#include <stdint.h>
#include "kernel/irq.h"
#include "kernel/framebuffer.h"
#include "irq_num.h"
#include "drivers/block/sdhci.h"
#include "zynq_usb.h"

extern uint32_t _seg_data;

void platform_init();

void platform_postinit();

extern fb_desc fb0;

#define MEM_BEGIN  (uint32_t     *) &_seg_data
#define MEM_END    (uint32_t     *)(0x20000000)

#define UART1      (zynq_uart    *)(0xe0001000) 

#define BOOT_CON   (UART1)

#define ETH0       (zynq_gem     *)(0xe000B000)

#define SD0        (sdhci        *)(0xe0100000)

#define USB0       (zynq_usb     *)(0xe0002000)

#define TTC0       (zynq_timer   *)(0xf8001000)

#define L2C0       (pl310        *)(0xf8f02000)

#define ZYNQ_SLCR_ADDR             (0xf8000000)
#define GIC_DIST   (pl390_dist   *)(0xf8f01000)
#define GIC_CPU    (pl390_cpu    *)(0xf8f00100)

#define ARCH_TIMER (cpu_priv_tmr *)(0xf8f00600)
#define TASK_SWITCH_IRQ nIRQ_PRIV_TMR

#define FB0     (display_surface *)(0x40000000)
#define PCM0    (pcm_channel     *)(0x40000000)

#define DEV_ROOTFS SD0

#define SCHED_KHZ  1
#define CPU_MHZ    650

#endif
