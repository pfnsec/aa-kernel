#ifndef MBR_H
#define MBR_H
#include "kernel/blockdev.h"

//Because the mbr partition entries lie on a 16-bit boundary, we have to 
//represent lba_start and size as arrays of uint8_t to avoid generating 
//an alignment fault. This is kind of a gross hack.

typedef struct mbr_part_t {
	uint8_t status;
	uint8_t chs_start[3];
	uint8_t type;
	uint8_t chs_end[3];
	uint8_t lba_start[4];
	uint8_t size[4];
} __attribute__((packed)) mbr_part_t;


typedef struct mbr_t {
	uint8_t bs_area[446];
	mbr_part_t ptable[4];
	uint16_t magic;
} __attribute__((packed,aligned(8))) mbr_t;


int mbr_scan(mbr_t *entry, volume *vol);


#endif 
