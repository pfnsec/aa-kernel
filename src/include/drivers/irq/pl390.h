#ifndef PL390_H
#define PL390_H
#include <stdint.h>

typedef volatile struct pl390_cpu {
	uint32_t control;
	uint32_t priority_mask;
	uint32_t binary_point;
	uint32_t irq_ack;
	uint32_t eoi;
	uint32_t run_priority;
	uint32_t hi_pend;
	uint32_t alias_binary_point;
} __attribute__((packed, aligned(4))) pl390_cpu;


typedef volatile struct pl390_dist {
	uint32_t enable;                //0x000
	uint32_t ic_type;               //0x004
	uint32_t dist_ident;            //0x008
	uint32_t pad[29];               //0x00c - 0x07c
	uint32_t irq_group[32];         //0x080 - 0x0fc
	uint32_t irq_enable_set[32];    //0x100 - 0x17c
	uint32_t irq_enable_clear[32];  //0x180 - 0x1fc
	uint32_t irq_pend_set[32];      //0x200 - 0x27c
	uint32_t irq_pend_clear[32];    //0x280 - 0x2fc
	uint32_t irq_active_status[32]; //0x300 - 0x37c
	uint32_t pad1[32];              //0x380 - 0x3fc
	uint8_t  irq_priority[1020];    //0x400 - 0x7fb
	uint32_t pad2;                  //0x7fc
	uint8_t  irq_target[1020];      //0x800 - 0xbfb
	uint32_t pad3;                  //0xbfc
	uint32_t irq_config[64];        //0xc00 - 0xcfc
	uint32_t irq_status[32];        //0xd00 - 0xd7c
	uint32_t pad4[32];              //0xd80 - 0xdfc
} __attribute__((packed, aligned(4))) pl390_dist;

void pl390_dist_init(pl390_dist *dev);

void pl390_cpu_init(pl390_cpu *dev);

#endif
