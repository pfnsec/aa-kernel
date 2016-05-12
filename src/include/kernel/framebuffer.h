#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include "registers.h"


typedef volatile struct fb_desc {
	unsigned int xres;	 	
	unsigned int yres;	 	
	unsigned int depth;	 	
	unsigned int pitch;	 	
	unsigned int colour_mode;	 	
	void *base;
} fb_desc;

#define COLOUR_RGB 0


void fb_clear(fb_desc *fb, addr_t colour);

void fb_base_alloc(fb_desc *);


#endif
