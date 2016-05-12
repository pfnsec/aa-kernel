#include <stdint.h>
#include "kernel/irq.h"
#include "kernel/thread.h"
#include "kernel/framebuffer.h"
#include "registers.h"
#include "platform.h"
#include "drivers/serial/pl011.h"
#include "drivers/framebuffer/pl110.h"
#include "pic.h"
#include "icp_timer.h"


fb_desc boot_fb_desc = {
	640,
	480,
	16,
	COLOUR_RGB,
};


void platform_init() {
	irq_register(pl011_irq_handler, irq_return, BOOT_CON_IRQ);
	irq_register(icp_timer_irq_handler, task_switch, TASK_SWITCH_IRQ);

	pl011_init(BOOT_CON);
	icp_timer_init(TIMER0, TIMER0_IRQ);

	fb_base_alloc(&boot_fb_desc);
	pl110_init(BOOT_FB, &boot_fb_desc);

}

