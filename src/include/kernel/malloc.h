#ifndef MALLOC_H
#define MALLOC_H
#include <stdint.h>

void alloc_init();

void *malloc(uint32_t);

void free(void *);

char *memcpy(char *, char *, uint32_t);

#endif
