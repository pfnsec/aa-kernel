#include <stdint.h>
#include "platform.h"
#include "kernel/console.h"
#include "zynq_slcr.h"

inline void zynq_slcr_write(uint32_t offset, uint32_t data) {
	*(volatile uint32_t *)(ZYNQ_SLCR_ADDR + offset) = data;
}

inline void zynq_slcr_set(uint32_t offset, uint32_t data) {
	*(volatile uint32_t *)(ZYNQ_SLCR_ADDR + offset) |= data;
}

inline void zynq_slcr_clear(uint32_t offset, uint32_t data) {
	*(volatile uint32_t *)(ZYNQ_SLCR_ADDR + offset) &= ~data;
}

inline uint32_t zynq_slcr_read(uint32_t offset) {
	return *(volatile uint32_t *)(ZYNQ_SLCR_ADDR + offset);
}


void zynq_slcr_lock() {
	if(!zynq_slcr_read(SLCR_LOCK_STATUS))
		zynq_slcr_write(SLCR_LOCK, 0x767B);

	if(!zynq_slcr_read(SLCR_LOCK_STATUS))
		printf("SLCR: Couldn't lock!\n");
}

void zynq_slcr_unlock() {
	if(zynq_slcr_read(SLCR_LOCK_STATUS))
		zynq_slcr_write(SLCR_UNLOCK, 0xDF0D);
	
	if(zynq_slcr_read(SLCR_LOCK_STATUS))
		printf("SLCR: Couldn't unlock!\n");
}

void zynq_slcr_sd_enable() {
	zynq_slcr_unlock();

	zynq_slcr_clear(SLCR_SDIO_RST_CTRL, (1 << 4) | 1);

	zynq_slcr_set(SLCR_APER_CLK_CTRL, (1 << 10));

	zynq_slcr_lock();
}

