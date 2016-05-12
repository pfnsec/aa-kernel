#include "kernel/framebuffer.h"
#include "drivers/framebuffer/pl110.h"


void pl110_init(pl110 *dev, fb_desc *fb) {
	dev->x_axis_control   = 0x3f1f3f9c;
	dev->y_axis_control   = 0x080b61df;
	dev->panel_base_upper = fb->base;
	dev->control          = 0x1829;
}



