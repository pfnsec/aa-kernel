#include <stdint.h>
#include <stdarg.h>
#include "kernel/console.h"


void puts(char *s) {
	if(s == 0) {
		puts("\\0");
		return;
	};

	for(int i = 0; s[i] != 0; i++) {
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

void puthex_64(uint64_t hex) {
	puthex_32(hex >> 32);
	puthex_32(hex);
}

void put_addr(void *addr) {
	#if   defined __aarch64__
		puthex_64((uint64_t) addr);
	#elif defined __arm__
		puthex_32((uint32_t) addr);
	#endif
}

void printf(char *s, ...) {
	va_list args;
	va_start(args, s);

	while(*s) {
		switch(*s) {
		case '%':
			switch(*(++s)) {
			case 's':
				puts(va_arg(args, char *));
				break;
			case 'b':
				puthex_8((uint8_t)va_arg(args,  int));
				break;
			case 'h':
				puthex_16((uint16_t)va_arg(args, int));
				break;
			case 'w':
				puthex_32((uint32_t)va_arg(args, int));
				break;
			case '%':
				putc('%');
				break;
			default:
				break;
			}

			break;

		default:
			putc(*s);

		}

		s++;
	}

	va_end(args);
}
