#include <stdint.h>
#include "platform.h"
#include "kernel/bb_alloc.h"
#include "kernel/blockdev.h"
#include "kernel/block_cache.h"

bc_t *bc_top = 0;

slab block_slab;


uint8_t *bc_lookup(uint32_t addr) {
	bc_t *bt;

	for(bt = bc_top; bt != 0; bt = bt->next) {
		if(bt) {
			if(bt->tag == (addr >> 16)) {
				if(bt->p->bc_a[(uint8_t)(addr >> 8)]) {
					return bt->p->bc_a[(uint8_t)(addr >> 8)]->bc_b[(uint8_t)(addr)];
				}
			}
		}
	} 

	return 0;
}


void bc_add(uint32_t addr, uint8_t *data) {
	bc_t *bt;

	for(bt = bc_top; bt != 0; bt = bt->next) {
		if(bt) {
			if(bt->tag == (addr >> 16)) {
				if(bt->p->bc_a[(uint8_t)(addr >> 8)]) {
					bt->p->bc_a[(uint8_t)(addr >> 8)]->bc_b[(uint8_t)(addr)] = data;
				} else {
					bt->p->bc_a[(uint8_t)(addr >> 8)] = malloc(sizeof(bc_bp));
					bt->p->bc_a[(uint8_t)(addr >> 8)]->bc_b[(uint8_t)(addr)] = data;
				}
			}
		}
	} 
}


void block_cache_init() {

	slab_create(&block_slab, 512, page_alloc(1));

	bc_top = malloc(sizeof(bc_t));

	bc_top->tag = 0;

	bc_top->p = malloc(sizeof(bc_ap));

	printf("block_cache_init()\n");

//	slab_create(&blkc_slab, sizeof(block_cache_t), page_alloc(1));
}

uint8_t *block_fetch(volume *vol, uint32_t addr) {
	uint8_t *r = 0;

	//r = bc_lookup(addr);

	if(!r) {
		r = slab_alloc(&block_slab);

		if(r) {
			block_read(vol, addr, r);
	//		bc_add(addr, r);
			return r;
		} else {
			return 0;
		}
	} else {
		return r;
	}

}

void block_free(uint8_t *r) {
	slab_free(&block_slab, r);
}
