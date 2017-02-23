#include <stdint.h>
#include "kernel/console.h"
#include "platform.h"


typedef volatile struct cpu_private_timer {
	uint32_t load;
	uint32_t counter;
	uint32_t control;
	uint32_t irq_status;
} __attribute__((packed)) cpu_priv_tmr;


void arch_timer_init() {
	uint32_t periphclk_mhz = CPU_MHZ/2;

	uint32_t prescale = 256; 
	uint32_t load = (periphclk_mhz * 1000)/(SCHED_KHZ * prescale);
//	uint32_t load = (periphclk_mhz * 1000000)/prescale;

	(ARCH_TIMER)->load = load - 1;
	(ARCH_TIMER)->control = ((prescale - 1) << 8) | 7;
}


void arch_timer_mspin(uint16_t ms) {
	while(1) {
		if((ARCH_TIMER)->irq_status) {
			ms--;
			(ARCH_TIMER)->irq_status = 1;
		}

		if(ms == 0) {
			return;
		}
	}
}


void arch_timer_isr(void *dev) {
	(ARCH_TIMER)->irq_status = 1;
}
