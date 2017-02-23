#include <stdint.h>
#include "arch.h"
#include "platform.h"
#include "drivers/irq/pl390.h"
#include "kernel/thread.h"
#include "kernel/irq.h"
#include "kernel/framebuffer.h"
#include "irq_num.h"
#include "zynq_uart.h"
#include "zynq_gem.h"
#include "zynq_timer.h"
#include "drivers/block/sdhci.h"
#include "drivers/framebuffer/display_surface.h"
#include "drivers/audio/pcm_channel.h"
#include "drivers/cache/pl310.h"

fb_desc fb0;


volume sd0 = {
	&blk_sdhci,
	
	0,
	0,

	0,
	0
};



void platform_init() {

	pl390_dist_init(GIC_DIST);
	pl390_cpu_init(GIC_CPU);

	pl310_init(L2C0);

	irq_register(arch_timer_isr, &task_switch, 0, TASK_SWITCH_IRQ);

	zynq_uart_irq_enable(BOOT_CON);

	irq_register(zynq_uart_isr, 0, BOOT_CON, nIRQ_UART1);

	display_surface_init(FB0, &fb0);
//	pcm_channel_init(PCM0);
//	irq_register(pcm_channel_isr, 0, PCM0, nIRQ_PL15);

	zynq_gem_init(ETH0);
	irq_register(zynq_gem_isr, 0, ETH0, nIRQ_ETH0);

	zynq_usb_init(USB0);
	irq_register(zynq_usb_isr, 0, USB0, nIRQ_USB0);

	sdhci_init(SD0);
	irq_register(sdhci_isr, 0, SD0, nIRQ_SD0);
	
}

void platform_postinit() {
	
	sdhci_card_reset(SD0);

	block_get_volumes(&sd0);

	if(volume_register(0, &sd0, "sd0")) {
		printf("platform_postinit(): failed to mount root (sd0)! \n");
	} else {
		printf("platform_postinit(): mounted root (sd0) \n");
	}
}
