#include <stdint.h>
#include "config.h"

uint32_t swi_handler(uint32_t n) {
	puthex_32(n);
	puts("\n");
	return n;
}
