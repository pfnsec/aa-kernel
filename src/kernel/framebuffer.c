#include "kernel/console.h"
#include "kernel/bb_alloc.h"
#include "kernel/framebuffer.h"
#include "registers.h"


void fb_clear(fb_desc *fb, uint32_t colour) {
	void *base;
	if(fb->active_buf)
		base = fb->base1;
	else
		base = fb->base0;

	if(fb->depth <= 8) {
		for(int i = 0; i < fb->xres * fb->yres; i++) {
			*(uint8_t *)(base + i) = (uint8_t)colour;
		}
	} else if(fb->depth <= 16) {
		for(int i = 0; i < fb->xres * fb->yres; i++) {
			*(uint16_t *)(base + (i * 2)) = (uint16_t)colour;
		}
	} else if(fb->depth <= 32) {
		for(int i = 0; i < fb->xres * fb->yres; i++) {
			*(uint32_t *)(base + (i * 4)) = (uint32_t)colour;
		}
	}
}

void *fb_base_alloc(fb_desc *fb) {
	int i;

	if(fb == 0)
		return 0;

	for(i = 0; i < 10; i++) {
		
		if((fb->xres * fb->yres * (fb->depth/8)) <= (PAGESIZE * (1 << i))) {
			return page_alloc(i);
		}
	}

	printf("fb_base_alloc(): Framebuffer too large\n");
	
	return 0;
}
