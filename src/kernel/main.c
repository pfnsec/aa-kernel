#include <stdint.h>
#include "kernel/console.h"
#include "kernel/bb_alloc.h"
#include "kernel/thread.h"
#include "kernel/irq.h"
#include "kernel/mutex.h"
#include "irq_num.h"
#include "kernel/framebuffer.h"
#include "registers.h"
#include "platform.h"


extern volume sd0;


void kmain() {

	platform_postinit();

	subvolume_scan(&sd0, "sd0");

//	do_ext2_mount();

}
