#ifndef DISPLAY_SURFACE_H
#define DISPLAY_SURFACE_H

#include <stdint.h>

typedef volatile struct display_surface {
	uint32_t cfg;
	uint32_t status;
	uint32_t base0;
	uint32_t base1;
	uint32_t dim;
	uint32_t active_buf;
} __attribute__((packed, aligned(4))) display_surface;

void display_surface_init(display_surface *dev, fb_desc *fb);

#endif
