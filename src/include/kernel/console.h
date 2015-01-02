#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdint.h>

void putc(char);
char getc();

void puts(char *);
void puthex_8(uint8_t);
void puthex_16(uint16_t);
void puthex_32(uint32_t);

#endif