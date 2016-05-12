#include "kernel/irq.h"
#include "platform.h"
#include "icp_timer.h"

void icp_timer_irq_clear(icp_timer *dev) {
	dev->irq_clear = 1;
}

void icp_timer_init(icp_timer *dev, int irq) {
	pic_irq_disable(irq);


	icp_timer_irq_clear(dev);

	dev->control  = 0x20;

	dev->control |= ICP_TIMER_PERIODIC;

	dev->control |= ICP_TIMER_32BIT;

//	dev->control |= ICP_TIMER_SCALE_16;
	dev->control |= ICP_TIMER_SCALE_256;

	dev->bg_load = 0xffffffff;

	dev->control |= ICP_TIMER_IRQ_ENABLE;

	dev->control |= ICP_TIMER_ENABLE;

	icp_timer_irq_clear(dev);

	pic_irq_enable(irq);
	
}


void icp_timer_irq_handler() {
	icp_timer_irq_clear(TIMER0); 
}
