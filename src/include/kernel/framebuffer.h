#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H
#include <stdint.h>

typedef volatile struct fb_desc {
	unsigned int xres;	 	
	unsigned int yres;	 	
	unsigned int depth;	 	
	unsigned int pitch;	 	
	unsigned int colour_mode;	 	
	int active_buf;
	int flags;
	void *base0;
	void *base1;
} fb_desc;

#define COLOUR_RGBA 0

#define FB_DOUBLE_BUFFERED 1

void fb_clear(fb_desc *fb, uint32_t colour);

void *fb_base_alloc(fb_desc *);


#endif
