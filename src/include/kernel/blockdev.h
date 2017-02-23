#ifndef BLOCKDEV_H
#define BLOCKDEV_H

#include <stdint.h>
#include "kernel/file.h"

struct blk_dev;
struct volume;

typedef struct blk_dev_ops {
	int  (*get_volumes)(struct blk_dev *dev, struct volume *vol);
	int  (*read_block)(struct blk_dev *dev, uint32_t blk_addr, uint8_t *dest);
	void (*sync)(struct blk_dev *dev);
} blk_dev_ops;


typedef struct blk_dev {
	const blk_dev_ops *op;
	void *reg;
} blk_dev;


//Describes an entry in /vol
typedef struct volfs_t {
	char *path;
} volfs_t;


typedef struct volume {
	const blk_dev *dev;

	struct volume *next;
	struct volume *subvolumes;
	
	uint32_t start;
	uint32_t end;
} volume;


typedef struct mount {
	const fs_ops *op;
	
	struct mount *next;
	struct mount *submounts;

	char *path;
	uint32_t flags;
} mount;


void block_init();

void volume_mount(volume *vol, char *path, uint32_t flags);

volume *mount_lookup(char *path, char **sub_path);

int get_volumes(volume *vol);

int block_read(volume *vol, uint32_t addr, uint8_t *dest);

void block_sync(volume *vol);

uint8_t *block_fetch(volume *vol, uint32_t addr);

#endif
