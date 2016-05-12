#ifndef ICP_TIMER_H
#define ICP_TIMER_H

#include <stdint.h>

typedef volatile struct icp_timer {
	uint32_t load;
	uint32_t value;
	uint32_t control;
	uint32_t irq_clear;
	uint32_t raw_irq_status;
	uint32_t mask_irq_status;
	uint32_t bg_load;
} __attribute__((packed)) icp_timer;


//icp_timer->control bitfields
#define ICP_TIMER_ENABLE     (1 << 7)
#define ICP_TIMER_PERIODIC   (1 << 6)
#define ICP_TIMER_IRQ_ENABLE (1 << 5)
#define ICP_TIMER_SCALE_16   (1 << 2)
#define ICP_TIMER_SCALE_256  (2 << 2)
#define ICP_TIMER_32BIT      (1 << 1)


void icp_timer_init(icp_timer *dev, int irq);

void icp_timer_irq_clear(icp_timer *dev);

void icp_timer_irq_handler();

#endif
