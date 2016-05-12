#include <stdint.h>
#include "platform.h"
#include "uart.h"

void platform_init() {

	sunxi_uart_init(BOOT_CON);

	for(int i = 0; i < 8; i++) {
		*(uint32_t *)(i) = interrupt_vector_table[i];
	}
}
