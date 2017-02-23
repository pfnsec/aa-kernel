#include <stdint.h>
#include "kernel/console.h"
#include "kernel/bb_alloc.h"
#include "kernel/blockdev.h"
#include "kernel/block_cache.h"
#include "kernel/file.h"
#include "kernel/mbr.h"

volume vol_root;

void block_init() {
	vol_root.dev = 0;

	vol_root.start = 0;
	vol_root.end = 0;

	vol_root.next = 0;
	vol_root.subvolumes = 0;

	block_cache_init();
}


int volume_register(volume *parent, volume *vol, char *devpath) {
	volume *pv = parent;
	volume *v;

	if(!vol || !devpath)
		return -1;

	if(pv == 0)
		pv = &vol_root;

	
	if(pv->subvolumes == 0) {
		pv->subvolumes = vol;
		return 0;
	} else {
		v = pv->subvolumes;

		do {

			if(v->next == 0) {
				v->next = vol;
				return 0;
			} else {
				v = v->next;
			}
		} while(v != 0);

		return 0;
	}
}


void volume_mount(volume *vol, char *path, uint32_t flags) {
	
}


int subvolume_scan(volume *vol, char *devpath) {
	uint8_t *r = block_fetch(vol, 0);	

	block_sync(vol);

	if(mbr_scan((mbr_t *)r, vol)) {
		printf("%s: Found MBR\n", devpath);
		block_free(r);
		return 0;
	} else {
		printf("%s: No MBR Found!\n", devpath);
		block_free(r);
		return -1;
	}

/*
	if(r && r[510] == 0x55 && r[511] == 0xAA) {
		printf("%s: Found MBR\n", devpath);
		new_vol = malloc(sizeof(volume));

		if(new_vol == 0) {
			printf("new_vol : alloc failed!\n");
			block_free(r);
			return -1;
		}

		new_vol->dev = vol->dev;

		mbr_entry((mbr_t *)(r + 0x1BE), new_vol);

		volume_register(vol, new_vol, devpath);

		block_free(r);
*/
}

int block_get_volumes(volume *vol) {
	vol->dev->op->get_volumes(vol->dev, vol);
}

int block_read(volume *vol, uint32_t addr, uint8_t *dest) {
	vol->dev->op->read_block(vol->dev, vol->start + addr, dest);
}

void block_sync(volume *vol) {
	vol->dev->op->sync(vol->dev);
}

