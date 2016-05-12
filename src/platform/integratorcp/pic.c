#include <stdint.h>
#include "registers.h"
#include "platform.h"
#include "pic.h"

void icp_pic_init(icp_pic *dev) {

}

void icp_pic_irq_enable(icp_pic *dev, addr_t bitmask) {
	dev->irq_enable_set |= bitmask;
}

void icp_pic_irq_disable (icp_pic *dev, addr_t bitmask) {
	dev->irq_enable_clear = bitmask;
}

void pic_irq_enable(addr_t bitmask) {
	icp_pic_irq_enable(PIC0, bitmask);
}

void pic_irq_disable(addr_t bitmask) {
	icp_pic_irq_disable(PIC0, bitmask);
}

addr_t pic_irq_status() {
	return (PIC0)->irq_status;
}
