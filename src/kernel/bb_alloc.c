#include "registers.h"
#include "platform.h"
#include "kernel/console.h"
#include "kernel/bb_alloc.h"



bb_alloc_t bb_head;

slab   bb_alloc_cache;



void bb_alloc_init() {

	//First page allocated for bb_alloc_t slab
	addr_t page_count = (MEM_END - MEM_BEGIN)/PAGESIZE - 1;
	int init_depth = 0;

	bb_head.next = 0;
	bb_head.free = 0;
	bb_head.addr = MEM_BEGIN;


	slab_create(&bb_alloc_cache, sizeof(bb_alloc_t), MEM_BEGIN);


	for(addr_t i = 0; i < WORDSIZE; i++) {
		if((page_count) & ((addr_t)1 << i)) {
			init_depth++;
		}
	}


	void *test;

	do {
		test = slab_alloc(&bb_alloc_cache);

		if((int)test % (32 * 5) == 0) {
			slab_free(&bb_alloc_cache, test);
		}

		put_addr(test);
		puts("\n");
		put_addr((void *)bb_alloc_cache.pages.blocks.free);
		puts("\n");

	} while(test != 0);

}


void slab_create(slab *cache, addr_t align, void *addr) {

	if(align > PAGESIZE)
		return;


	cache->alignment = align;

	cache->pages.addr = addr;

	//If we can store at least WORDSIZE entries within a single page, 
	//each block is capable of tracking WORDSIZE entries.
	//Otherwise, we must set the 'free' bits to indicate the true number
	//of valid entries per block.

	if(BLOCKSIZE(align) <= PAGESIZE) {
		cache->pages.blocks.free = ~((addr_t)(0));
	} else {
		cache->pages.blocks.free =  ((addr_t)(1) << PAGESIZE/align) - 1;
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
	static int lookup_cache[LKUP_ORDER] = {0};
	int next_order = order - 1;

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


	do {
		block = &page->blocks;

		block_index = 0;

		do {

			block_index++;

			if(slab_search_free(block, LKUP_ORDER, 0, &found_free)) {
				block->free &= ~((addr_t)1 << found_free);
				return (void *)(page->addr + (block_index * BLOCKSIZE(cache->alignment)) + (found_free * cache->alignment));
			}

			block = block->next;

		} while(block != 0);

		page = page->next;

	} while(page != 0);

	return 0;
}

void slab_free(slab *cache, void *p) {
	addr_t addr_offset;
	int    entry_offset;

	slab_page_list  *page  = &cache->pages;
	slab_block_list *block = &page->blocks;


	if(cache == 0 || p == 0)
		return;


	if(page == 0)
		return;


	if(block == 0)
		return;

	do {
		addr_offset = p - page->addr;

		if(addr_offset > PAGESIZE) {
			//Address not in current range
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

