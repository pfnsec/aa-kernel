#include <stdint.h>
#include "peripherals.h"
#include "mailbox.h"
#include "rpi_framebuffer.h"
#include "kernel/thread.h"


rpi_fb_info init_fb = {
	.phys_width  = 640, 
	.phys_height = 480,
	.virt_width  = 640, 
	.virt_height = 480,
	.depth       = 32
	};


void rpi_framebuffer_init() {
	do {
		mailbox_write_spin(MAILBOX_CHAN_FB, periph_bus_addr(&init_fb));
	}
	while(mailbox_read_spin(MAILBOX_CHAN_FB) != 0);
}

void trip_balls() {
	uint8_t r = 0, g = 0, b = 0;
	int x = 0, y = 0;

	uint32_t colour = 0;

	uint32_t *fb = (uint32_t *)(periph_phy_addr(init_fb.addr));

	while(1) {

		r = (x  % (1 << 9));
		g = (y  % (1 << 9));
		g = ((x * y) % (1 << 9));

		//fb[(y * init_fb.pitch) + (x * 3) + 0] = r;
		//fb[(y * init_fb.pitch) + (x * 3) + 1] = g;
		//fb[(y * init_fb.pitch) + (x * 3) + 2] = b;
		//

		fb[(y * init_fb.pitch) + x] = colour;

		x++;

		colour++;

		yield();
		if(x >= 640) { 
			x = 0;
			y++;

			if(y >= 480){
				y = 0;
			}
		}
	}
}
