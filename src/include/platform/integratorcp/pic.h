#ifndef PIC_H
#define PIC_H
#include <stdint.h>
#include "registers.h"

typedef volatile struct icp_pic {
	uint32_t irq_status;
	uint32_t irq_raw_status;
	uint32_t irq_enable_set;
	uint32_t irq_enable_clear;
} __attribute__((packed)) icp_pic;


#define PIC_IRQ_TIMER0 (1 << 5)
#define PIC_IRQ_UART0  (1 << 1)


void icp_pic_init(icp_pic *dev);

void icp_pic_irq_enable  (icp_pic *dev, addr_t bitmask);

void icp_pic_irq_disable (icp_pic *dev, addr_t bitmask);


#endif
