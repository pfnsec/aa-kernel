#include "arch.h"

void subarch_init() {
	arch_timer_init();

	scu_init();
}
