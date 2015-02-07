#include <stdint.h>
#include "config.h"
#include "thread.h"
#include "sched.h"

uint32_t swi_handler(uint32_t n) {
	if(n == 1) {
		yield();
	}
	return n;
}
