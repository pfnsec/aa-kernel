#include <stdint.h>
#include "kernel/framebuffer.h"
#include "platform.h"
#include "gpio.h"
#include "rpi_framebuffer.h"

fb_desc boot_fb_desc = {
	640,
	480,
	16,
	COLOUR_RGB,
};

void platform_init() {
	rpi_framebuffer_init();
	
	for(int i = 0; i < 8; i++) {
		*(uint32_t *)(i * 4) = *(uint32_t *)(&interrupt_vector_table + i * 4);
	}
}
