#include "registers.h"
#include "platform.h"
#include "kernel/console.h"
#include "kernel/bb_alloc.h"
#include "kernel/malloc.h"



bb_alloc_t bb_head;

slab bb_alloc_cache;



void bb_alloc_init() {

	//First page allocated for bb_alloc_t slab
	addr_t page_count = ((MEM_END - MEM_BEGIN)/PAGESIZE) - 1;

	int init_depth = 0;

	bb_head.size = 0;
	bb_head.addr = MEM_BEGIN;
	bb_head.free = 0;
	bb_head.next = 0;

	slab_create(&bb_alloc_cache, sizeof(bb_alloc_t), MEM_BEGIN);

//	printf("bb_alloc_init(): page_count = %w\n", page_count);

	bb_alloc_t *bb_entry = &bb_head;

	for(addr_t i = 1; i < WORDSIZE; i++) {


		if((page_count) & ((addr_t)1 << i)) {
			init_depth++;

			void        *bb_entry_addr = bb_entry->addr;
			unsigned int bb_entry_size = bb_entry->size;


			bb_entry->next = slab_alloc(&bb_alloc_cache);

			if(bb_entry->next == 0) {
				puts("bb_alloc_init(): Failed to allocate a page descriptor from bb_alloc_cache!\n");
			}

			bb_entry = bb_entry->next;
			bb_entry->size = i;
			bb_entry->addr = bb_entry_addr + (1 << bb_entry_size) * PAGESIZE;
			bb_entry->free = 1;
			bb_entry->next = 0;
		}
	}



}


void *page_alloc(int n) {
//	printf("page_alloc(n = %w)\n", n); 
	bb_alloc_t *curr_entry = &bb_head;
	bb_alloc_t *prev_entry = &bb_head;

	do {

		if(((1 << curr_entry->size) == n ) && curr_entry->free) {

			curr_entry->free = 0;

			return curr_entry->addr;

		} else if(((1 << curr_entry->size) > n) && curr_entry->free) {

			//Split a buddy-block of 2^size pages into 2 of 2^(size - 1) pages,
			//inserting the new entry before the current entry
			prev_entry->next = slab_alloc(&bb_alloc_cache);

			if(!prev_entry->next)
				return 0;

			prev_entry->next->size = curr_entry->size - 1;
			curr_entry->size       = curr_entry->size - 1;

			prev_entry->next->next = curr_entry;

			prev_entry->next->addr = curr_entry->addr;
			curr_entry->addr       = curr_entry->addr + ((1 << curr_entry->size) * PAGESIZE);
			prev_entry->next->free = 1;

			curr_entry = prev_entry->next;

		} else {
			prev_entry  = curr_entry;
			curr_entry  = curr_entry->next;
		}
	} while(curr_entry != 0);

	return 0;

}



void slab_create(slab *cache, addr_t align, void *addr) {

	if(align > PAGESIZE)
		return;

	cache->alignment = align;

	cache->pages.addr = addr;

	//If we can store at least [32|64] entries within a single page, 
	//each block bitmap is capable of tracking entries.
	//Otherwise, we must set the 'free' bits to indicate the true number
	//of valid entries per block.

	if(BLOCKSIZE(align) <= PAGESIZE) {
		cache->pages.blocks.free = ~(0UL);
	} else {
		cache->pages.blocks.free =  ((1UL) << PAGESIZE/align) - 1;
	}
}

slab_block_list *block_extend(slab *cache) {
	uint32_t count = PAGESIZE;

	if(BLOCKSIZE(cache->alignment) > PAGESIZE) {
	}


	while(count > 0) {
		
	}
}

slab_page_list *slab_extend(slab *cache) {

	slab_page_list *page = malloc(sizeof(slab_page_list));

	page->addr = page_alloc(1);

//	page->block.

	page->next = 0;

	if(BLOCKSIZE(cache->alignment) <= PAGESIZE) {
		page->blocks.free = ~(0UL);
	} else {
		page->blocks.free =  ((1UL) << PAGESIZE/cache->alignment) - 1;
	}
}

#define LKUP_TOP 2
#define LKUP_BOT 1

#if(WORDSIZE == 64)
	#define LKUP_ORDER 6
#elif(WORDSIZE == 32)
	#define LKUP_ORDER 5
#endif


int slab_search_free(slab_block_list *block, int order, int offset, int *result) {
//	printf("slab_search_free(block = %w, order = %w, offset = %w, result = %w)\n", block, order, offset, result);
	static int lookup_cache[LKUP_ORDER] = {0};
	int next_order = order - 1;

	//High and Low indexes into the 
	int offset_top = (offset + (1 << next_order));
	int offset_bot = (offset);
	addr_t bitmask;

	*result = offset;

	if(order == 1) {
		if(block->free & ((addr_t)1 << offset_bot)) {
			*result = offset_bot;
			return 1;
		} else if(block->free & ((addr_t)1 << offset_top)) {
			*result = offset_top;
			return 1;
		} else {
			return 0;
		}
	} else if(order < LKUP_ORDER) {

		//block->free & ((2^(2^order) - 1) << offset)
		//E.G. at order 3 & offset 0,  block->free & 0xff
		//     at order 4 & offset 16, block->free & 0xffff0000, etc.
		bitmask = (addr_t)(((addr_t)1 << ((addr_t)1 << order)) - 1) << offset;

		//All entries in curent subtree free? Don't recurse further.
		if((block->free & bitmask) == bitmask)  {
			return 1;
		} else if(block->free & bitmask)  {
			if(slab_search_free(block, next_order, offset_bot, result)) {

				lookup_cache[order] = LKUP_BOT;

				return 1;

			} else if(slab_search_free(block, next_order, offset_top, result)) {

				lookup_cache[order] = LKUP_TOP;

				return 1;

			} else 
				return 0;

		} else 
			return 0;

	} else {

		bitmask = ~(addr_t)(0);

		//All entries in block free? Don't recurse further.
		if((block->free & bitmask) == bitmask)  {
			return 1;
		} else if(block->free) {
			if(slab_search_free(block, next_order, offset_bot, result)) {

				lookup_cache[order] = LKUP_BOT;

				return 1;

			} else if(slab_search_free(block, next_order, offset_top, result)) {

				lookup_cache[order] = LKUP_TOP;

				return 1;

			} else
				return 0;
		} else
			return 0;
	}
}


void *slab_alloc(slab *cache) {
	//Index into page.blocks
	int block_index;

	//Entry index into the target block;
	int found_free; 

	if(cache == 0)
		return 0;


	slab_page_list  *page  = &cache->pages;

	if(page == 0)
		return 0;

	slab_block_list *block = &page->blocks;

	if(block == 0)
		return 0;

//	printf("slab_alloc(cache = %w, block = %w, free = %w\n", cache, block, block->free);

	do {
		block = &page->blocks;

		block_index = 0;

		do {

			block_index++;

			if(slab_search_free(block, LKUP_ORDER, 0, &found_free)) {
				block->free &= ~(1UL << found_free);
				return (void *)(page->addr + (block_index * BLOCKSIZE(cache->alignment)) + (found_free * cache->alignment));
			}

			block = block->next;

		} while(block != 0);

		page = page->next;

	} while(page->next != 0);

	//Here, we are out of pages in the current cache and must allocate another.
	//There exists an infinite recursion hazard if the cache is that used to allocate pages in the first place!

	if(cache == &bb_alloc_cache) {
		printf("bb_alloc_cache has eaten itself!\n");
		return 0;
	} else {
		slab_extend(cache);
		page->next = malloc(sizeof(slab_page_list));
		page = page->next;
		printf("bb_alloc_cache has eaten itself!\n");
	}

	

}

void slab_free(slab *cache, void *p) {
	addr_t addr_offset;
	int    entry_offset;


	if(cache == 0 || p == 0)
		return;


	slab_page_list  *page  = &cache->pages;

	if(page == 0)
		return;


	slab_block_list *block = &page->blocks;

	if(block == 0)
		return;


	do {
		addr_offset = p - page->addr;

		if(addr_offset > PAGESIZE) {
			//Address not in current page list
			continue;
		} else if ((addr_offset  % cache->alignment) != 0) {
			//In range, but invalid entry (unaligned)
			return;
		} else {

			entry_offset = (addr_offset/cache->alignment) % WORDSIZE;
			block = &cache->pages.blocks;

			puts("entry_offset: ");
			puthex_32(entry_offset);
			puts("\n");

			//(addr_offset/BLOCKSIZE(align)) yields the number of blocks up to and 
			//including the block containing p; we iterate up to this block and mark 
			//the corresponding entry as free.
			

			for(int i = 1; i < (addr_offset / BLOCKSIZE(cache->alignment)); i++) {

				if(block->next != 0) {
					block = block->next;
				} else {
					return;
				}
			}

			block->free |= (1 << entry_offset);
		}

		page = page->next;
	} while(page != 0);
}
