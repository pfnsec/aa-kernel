#include "kernel/malloc.h"
#include "kernel/framebuffer.h"
#include "registers.h"


void fb_clear(fb_desc *fb, addr_t colour) {
	if(fb->depth <= 8) {
		for(int i = 0; i < fb->xres * fb->yres; i++) {
			*(uint8_t *)(fb->base + i) = (uint8_t)colour;
		}
	} else if(fb->depth <= 16) {
		for(int i = 0; i < fb->xres * fb->yres; i++) {
			*(uint16_t *)(fb->base + (i * 2)) = (uint16_t)colour;
		}
	}
}

void fb_base_alloc(fb_desc *fb) {
	if(fb == 0)
		return;

	fb->base = malloc(fb->xres * fb->yres * (fb->depth/8));

	
}
