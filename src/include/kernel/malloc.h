#ifndef MALLOC_H
#define MALLOC_H
#include <stdint.h>

//alloc_t - linked list of memory allocations

typedef struct alloc_t {
	int free;
	void *start;
	void *end;
	struct alloc_t *next;
} alloc_t;


//page_pool - suballocator sitting on top of the slab cache and page allocator.

typedef struct page_pool {
	alloc_t *head;
	int extendable;
	int depth_extendable;
	int page_count; 
	int alloc_depth;
} page_pool;

void alloc_init();

void *malloc(uint32_t);

void free(void *);

char *memcpy(char *, char *, uint32_t);


#endif
