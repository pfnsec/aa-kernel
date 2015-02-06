#include <stdint.h>
#include "config.h"
#include "kernel/console.h"


void puts(char *s) {
	int i;
	for(i = 0; s[i] != 0; i++) {
		putc(s[i]);
	}
}

void puthex_8(uint8_t hex) {
	char conv_table[16] = {
		'0', '1', '2', '3',
		'4', '5', '6', '7',
		'8', '9', 'A', 'B',
		'C', 'D', 'E', 'F'};


	putc(conv_table[hex >> 4]);
	putc(conv_table[hex % 16]);
		
}

void puthex_16(uint16_t hex) {
	puthex_8(hex >> 8);
	puthex_8(hex);
}

void puthex_32(uint32_t hex) {
	puthex_16(hex >> 16);
	puthex_16(hex);
}
