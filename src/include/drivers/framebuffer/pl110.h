#ifndef PL110_H
#define PL110_H

#include <stdint.h>
#include "registers.h"
#include "kernel/framebuffer.h"


typedef struct pl110 {
	uint32_t x_axis_control;
	uint32_t y_axis_control;
	uint32_t clk_control;
	uint32_t line_end;
	uint32_t panel_base_upper;
	uint32_t panel_base_lower;
	uint32_t irq_enable_mask;
	uint32_t control;
} pl110;

void pl110_init(pl110 *, fb_desc *);


#endif
