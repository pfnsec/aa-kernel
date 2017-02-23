#include "registers.h"
#include "platform.h"
#include "kernel/console.h"
#include "kernel/bb_alloc.h"
#include "kernel/malloc.h"
#include <stdint.h>


alloc_t *alloc_head;
slab     alloc_cache;

void print_alloc_table();

//Allocate 2^depth pages when we exhaust the current page pool
int alloc_page_depth = 1;


void extend_page_pool(page_pool *p) {
	alloc_t *a = p->head;

	do {
		if(a->next == 0) {
			a->next = slab_alloc(&alloc_cache);

			if(a->next == 0) {
				printf("extend_page_pool(%w) failed to extend allocation table!\n", p);
				return;
			}

			a->next->start = page_alloc((1 << p->alloc_depth));

			if(a->start == 0) {
				printf("extend_page_pool(%w): failed to allocate page(s)!\n", p);

				printf("\textendable = %b\n", p->extendable);

				printf("\tdepth_extendable = %b\n", p->depth_extendable); 

				printf("\tpage_count = %w\n", p->page_count); 

				printf("\talloc_depth = %b\n", p->alloc_depth); 

				slab_free(&alloc_cache, a);
				a->next = 0;

			} else {
				a->next->end     = a->start + (1 << p->alloc_depth) * PAGESIZE;
				a->next->free    = 1;
				a->next->next    = 0;
			}
		}

		a = a->next;
	} while(a != 0);

}


void alloc_init() {

	slab_create(&alloc_cache, sizeof(alloc_t), page_alloc(1));

	alloc_head = slab_alloc(&alloc_cache);

	if(!alloc_head)
		printf("alloc_init(): couldn't create alloc_head!");

	alloc_head->free = 1;
	alloc_head->start = page_alloc((1 << alloc_page_depth));
	alloc_head->end = alloc_head->start + ((1 << alloc_page_depth) * PAGESIZE);
	alloc_head->next = 0;

/*
	printf("alloc_init():\n \
	         alloc_head : %w \n \
	         alloc_head->start : %w \n \
	         alloc_head->end : %w \n \
	         alloc_head->next : %w\n", 
	       alloc_head, 
	       alloc_head->start, 
	       alloc_head->end, 
               alloc_head->next);
*/
}


//Split an allocation entry into two blocks, one of a specified size
uint32_t split(alloc_t *entry, uint32_t size) {
	alloc_t *new_entry;

	if(entry->end - entry->start < size) {
		return 0;
	} else if(entry->end - entry->start == size) {
		return size;
	}

	new_entry          = (alloc_t *)slab_alloc(&alloc_cache);

	if(new_entry == 0) {
		printf("split(%w, %w): failed to allocate entry\n", entry, size);
		return 0;
	}

	new_entry->free  = 1;
	new_entry->start = entry->start + size;
	new_entry->end   = entry->end;

	//insert into allocation table
	new_entry->next = entry->next;
	entry->next = new_entry;

	entry->end = entry->start + size;

//	printf("split(0x%w, %w):\n entry->free : %w \n entry->start : %w \n entry->end : %w\n entry->next : %w \n", entry, size, entry->free, entry->start, entry->end, entry->next);
//	printf("split(0x%w, %w):\n new_entry->free : %w \n new_entry->start : %w \n new_entry->end : %w\n new_entry->next : %w \n", new_entry, size, new_entry->free, new_entry->start, new_entry->end, new_entry->next);
	return new_entry->end - new_entry->start;
}



void *malloc(uint32_t size) {
	alloc_t *cur;

	if(size > (1 << alloc_page_depth) * PAGESIZE) {
		int i;


	}

	//Search for a large enough block
	for(cur = alloc_head; cur != 0; cur = cur->next) {

		if(cur->free != 1 || (cur->end - cur->start) < size) {
			continue;
		}

		if(split(cur, size) == 0) {
			continue;
		}

		if(cur->start != 0) {
			cur->free = 0;
//			printf("malloc():\n cur : %w \n cur->start : %w \n cur->end : %w \n cur->next : %w\n", cur, cur->start, cur->end, cur->next);
			return cur->start;
		}
	}

	printf("Alloc of size 0x%w failed!\n", size);

	return 0;
}


void alloc_test(int size) {
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

	for(i = 0; i < size; i++) {
		if(!(a[i] == 'a' &&
	 	     b[i] == 'b' &&
		     c[i] == 'c' &&
		     d[i] == 'd')) {
			puts("Error: alloc_test(): Memory regions not separate!\n");
		}
	}


	print_alloc_table();
}


void free(void *addr) {
	alloc_t *cur;

	for(cur = alloc_head; cur != 0; cur = cur->next) {
		if(cur->start == addr)
			cur->free = 1;
	}
}


//Combine adjacent free blocks 
void reclaim_fragments() {
	alloc_t *blk1, *blk2;

	for(blk1 = alloc_head; blk1 != 0; blk1 = blk1->next) {
		blk2 = blk1->next;

		if(blk1->free && blk2->free) {
			blk1->next = blk2->next;
			blk1->end  = blk2->end;
			slab_free(&alloc_cache, blk2);
		}
	}
}


char *memcpy(char *s1, char *s2, uint32_t n) {
	uint32_t offset;

	for(offset = 0; offset < n; offset++) {
		s1[offset] = s2[offset];
	}

	return s1;
}

void memset(char *s1, int t, uint32_t n) {
	uint32_t offset;

	for(offset = 0; offset < n; offset++) {
		s1[offset] = t;
	}
}

void print_alloc_table() {
	alloc_t *cur;

	for(cur = alloc_head; cur != 0; cur = cur->next) {
		printf("%w:\n", cur);
		printf("%w : %w", cur->start, cur->end - cur->start);
		if(cur->free) 
			puts(" (free)\n");
		else
			putc('\n');
	}
}

