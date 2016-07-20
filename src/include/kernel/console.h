#ifndef CONSOLE_H
#define CONSOLE_H
#include <stdint.h>
#include <stdarg.h>

void putc(char);
char getc();

void puts(char *);
void puthex_8(uint8_t);
void puthex_16(uint16_t);
void puthex_32(uint32_t);

void put_addr(void *);

void printf(char *, ...);


#endif
