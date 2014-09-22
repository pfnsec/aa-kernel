#ifndef MALLOC_H
#define MALLOC_H
#include <stdint.h>

void init_alloc_table();

void *malloc(uint32_t);

void free(void *);

char *memcpy(char *, char *, uint32_t);

#endif
