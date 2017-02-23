#ifndef BLOCK_CACHE_H
#define BLOCK_CACHE_H

#include <stdint.h>
#include "kernel/blockdev.h"


/*
typedef struct bc_bp {
	uint8_t *block[256];
} __attribute__((aligned(4))) bc_bp;
*/


typedef struct bc_bp {
	uint8_t *bc_b[256];
} __attribute__((aligned(4))) bc_bp;


typedef struct bc_ap {
	bc_bp *bc_a[256];
} __attribute__((aligned(4))) bc_ap;


typedef struct bc_t {
	uint16_t tag;
	bc_ap *p;

	struct bc_t *next;
} bc_t;


typedef struct block_cache_t {
	uint8_t *addr;
	uint32_t blk_addr;
	int free;
} block_cache_t;



uint8_t *block_fetch(volume *vol, uint32_t addr);



#endif
