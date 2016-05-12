#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>


typedef volatile struct rpi_fb_info {
	uint32_t phys_height;
	uint32_t phys_width;
	uint32_t virt_height;
	uint32_t virt_width;
	uint32_t pitch;
	uint32_t depth;
	uint32_t x_offset;
	uint32_t y_offset;
	void    *addr;
	uint32_t size;

} __attribute__((packed, aligned(16))) rpi_fb_info;


void rpi_framebuffer_init();



#endif
