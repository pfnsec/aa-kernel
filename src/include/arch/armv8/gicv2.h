#ifndef GICV2_H
#define GICV2_H
#include <stdint.h>


typedef struct gicv2_dist {
	uint32_t ctl;
	uint32_t type;
	uint32_t pad0        [29];
	uint32_t group       [32];
	uint32_t set_enable  [32];
	uint32_t clr_enable  [32];
	uint32_t set_pend    [32];
	uint32_t clr_pend    [32];
	uint32_t set_active  [32];
	uint32_t clr_active  [32];
	uint32_t priority    [255];
	uint32_t targets     [255];
	uint32_t config      [64];
	uint32_t pad1        [128];
	uint32_t sgi;
	uint32_t pad2        [3];
	uint32_t sgi_clr_pend[4];
	uint32_t sgi_set_pend[4];
} __attribute__((packed)) gicv2_dist;

typedef struct gicv2_cpu {
	uint32_t ctl;
	uint32_t pri_mask;
	uint32_t bin_point;
	uint32_t irq_ack;
	uint32_t eoi;
	uint32_t hpri_pending;
} __attribute__((packed)) gicv2_cpu;



#endif
