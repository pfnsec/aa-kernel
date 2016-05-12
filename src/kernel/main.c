#include "kernel/console.h"
#include "kernel/thread.h"
#include "kernel/irq.h"
#include "kernel/framebuffer.h"
#include "registers.h"
#include "platform.h"



void kmain() {
//	fb_clear(&boot_fb_desc, (67 << 4));
	bb_alloc_init();

	while(1); 
}

