#include "kernel/console.h"
#include "platform.h"
#include <stdint.h>

extern uint32_t _seg_data;

#define MEM_BEGIN &_seg_data

#ifndef MEM_END //platform.h
#define MEM_END (MEM_BEGIN + 0x08000000)
#endif


typedef struct alloc_t {
	int free;
	void *address;
	uint32_t size;
	struct alloc_t *next;
} alloc_t;


alloc_t alloc_head;


void init_alloc_table() {
	alloc_head.free = 1;
	alloc_head.address = (void *)MEM_BEGIN + sizeof(alloc_t);
	alloc_head.size = (MEM_END - MEM_BEGIN);
	alloc_head.next = 0;
}


//split an allocation block into two, one of size bytes and return the size of the other
//returns 0 on failure
uint32_t split(alloc_t *entry, uint32_t bytes) {
	alloc_t *new_entry;

	if(entry->size <= bytes + sizeof(alloc_t))
		return 0;

	new_entry = (alloc_t *)(entry->address + bytes);
	new_entry->free = 1;
	new_entry->address = (void *)new_entry + sizeof(alloc_t);
	new_entry->size = entry->size - (bytes + sizeof(alloc_t));

	//insert into allocation table
	new_entry->next = entry->next;
	entry->next = new_entry;

	//entry->size -= new_entry->size + sizeof(alloc_t);
	entry->size = bytes;
	return new_entry->size;
}


void print_alloc_table() {
	alloc_t *cur;

	for(cur = &alloc_head; cur != 0; cur = cur->next) {
		puthex_32((uint32_t) cur);
		puts(":\n");
		puthex_32((uint32_t) cur->address);
		puts(" : ");
		puthex_32((uint32_t) cur->size);
		if(cur->free) puts(" (free)\n");
		putc('\n');
	}
}


void *malloc(uint32_t size) {
	alloc_t *cur;

	for(cur = &alloc_head; cur != 0; cur = cur->next) {
		//iterate until we find a free block large enough
		if(cur->free != 1 || cur->size < (size + sizeof(alloc_t)))
			continue;

		if(split(cur, size) == 0) {
			continue;
		}
		cur->free = 0;
		return cur->address;
	}
	puts("Alloc of size 0x");
	puthex_32(size);
	puts(" failed!\n");
	return 0;
}


void alloc_test(size) {
	int i;
	char *a, *b, *c, *d;

	a = malloc(size);
	b = malloc(size);
	c = malloc(size);
	d = malloc(size);

	for(i = 0; i < size; i++) {
		a[i] = 'a';
		b[i] = 'b';
		c[i] = 'c';
		d[i] = 'd';
	}
	a[size] = '\n';
	b[size] = '\n';
	c[size] = '\n';
	d[size] = '\n';


	print_alloc_table();
}


void free(void *addr) {
	alloc_t *cur;

	for(cur = &alloc_head; cur != 0; cur = cur->next) {
		if(cur->address == addr)
			cur->free = 1;
	}
}


//combines blocks into contiguous areas where possible
void reclaim_fragments() {
	alloc_t *blk1, *blk2;

	for(blk1 = &alloc_head; blk1 != 0; blk1 = blk1->next) {
		blk2 = blk1->next;
		if(blk1->free && blk2->free) {
			blk1->next = blk2->next;
			blk1->size += (blk2->size + sizeof(alloc_t));
		} else continue;
	}
}


char *memcpy(char *s1, char *s2, uint32_t n) {
	uint32_t offset;

	for(offset = 0; offset < n; offset++) {
		s1[offset] = s2[offset];
	}

	return s1;
}
