#include <stdint.h>
#include "registers.h"
#include "platform.h"
#include "kernel/console.h"
#include "kernel/irq.h"
#include "drivers/irq/pl390.h"


void pl390_write_bit(volatile uint32_t *base, int n) {
	base[(n/32)] = (1 << (n % 32));
}

void pl390_set_bit(volatile uint32_t *base, int n) {
	base[(n/32)] |= (1 << (n % 32));
}

void pl390_clear_bit(volatile uint32_t *base, int n) {
	base[(n/32)] &= ~(1 << (n % 32));
}

int pl390_test_bit(volatile uint32_t *base, int n) {
	if((base[(n/32)]) & (1 << (n % 32))) {
		return 1;
	} else {
		return 0;
	}
}


void pl390_dist_init(pl390_dist *dev) {
	dev->enable = 0;
}

void pl390_cpu_init(pl390_cpu *dev) {
	dev->control = 0;
	dev->priority_mask = 0xffff;
}

void pl390_dist_enable(pl390_dist *dev) {
	dev->enable = 3;
}

void pl390_cpu_enable(pl390_cpu *dev) {
	dev->control = 3;
}

void pl390_dist_disable(pl390_dist *dev) {
	dev->enable = 0;
}

void pl390_cpu_disable(pl390_cpu *dev) {
	dev->control = 0;
}

void pl390_enable_set(pl390_dist *dev, int nirq) {
	pl390_write_bit(dev->irq_enable_set, nirq);
}

void pl390_enable_clear(pl390_dist *dev, int nirq) {
	pl390_write_bit(dev->irq_enable_clear, nirq);
}


void pl390_pending_set(pl390_dist *dev, int nirq) {
	pl390_write_bit(dev->irq_pend_set, nirq);
}

void pl390_pending_clear(pl390_dist *dev, int nirq) {
	pl390_write_bit(dev->irq_pend_clear, nirq);
}


unsigned int pic_irq_get_pending() {
	return (0x3FF) & (GIC_CPU)->irq_ack;
}


void pic_irq_eoi(unsigned int n) {
	(GIC_CPU)->eoi =  (0x3FF) & n;
}

void (*irq_top_handler(void))() {
	uint16_t n;

//	putc('!');

	n = pic_irq_get_pending();

//	puthex_32((GIC_DIST)->irq_active_status);

	if(n >= 1020) {
		return &irq_return;
	}

	return (irq_handle(n));

}


int pic_irq_pending(unsigned int nirq) {
	return pl390_test_bit((GIC_DIST)->irq_pend_set, nirq);
}

void pic_irq_clear(unsigned int nirq) {
//	pl390_dist_disable(GIC_DIST);
//	pl390_cpu_disable(GIC_CPU);

	pl390_write_bit((GIC_DIST)->irq_pend_clear, nirq);

//	pl390_dist_enable(GIC_DIST);
//	pl390_cpu_enable(GIC_CPU);
}

void pic_irq_enable(unsigned int nirq) {
	pl390_dist_disable(GIC_DIST);
	pl390_cpu_disable(GIC_CPU);

	//Target first core
	(GIC_DIST)->irq_target[nirq] = 0x01;

	//Set Group 0 (Secure Mode)
	pl390_clear_bit((GIC_DIST)->irq_group, nirq);

	//Set Edge-Triggered
//	pl390_set_bit((GIC_DIST)->irq_config, (2 * nirq + 1));
	
	pl390_write_bit((GIC_DIST)->irq_enable_set, nirq);

	pl390_dist_enable(GIC_DIST);
	pl390_cpu_enable(GIC_CPU);
}
void pic_irq_disable(unsigned int nirq) {
	pl390_dist_disable(GIC_DIST);
	pl390_cpu_disable(GIC_CPU);

	pl390_set_bit((GIC_DIST)->irq_enable_clear, nirq);

	pl390_dist_enable(GIC_DIST);
	pl390_cpu_enable(GIC_CPU);
}

void dump_pl390_state() {
	int i;
	puts("\ncontrol:"); 
	puthex_32((GIC_CPU)->control);
	puts("\npriority_mask:"); 
	puthex_32((GIC_CPU)->priority_mask);
	puts("\nbinary_point:"); 
	puthex_32((GIC_CPU)->binary_point);
	puts("\neoi:"); 
	puthex_32((GIC_CPU)->eoi);
	puts("\nrun_priority:"); 
	puthex_32((GIC_CPU)->run_priority);
	puts("\nhi_pend:"); 
	puthex_32((GIC_CPU)->hi_pend);
	puts("\nalias_binary_point:"); 
	puthex_32((GIC_CPU)->alias_binary_point);

	puts("\nenable");                //0x000
	puthex_32((GIC_DIST)->enable);
	puts("\nic_type");               //0x004
	puthex_32((GIC_DIST)->ic_type);
	puts("\ndist_ident");            //0x008
	puthex_32((GIC_DIST)->dist_ident);
	puts("\npad");               //0x00c - 0x07c
	for(i = 0; i < 29; i++) {
		puthex_32((GIC_DIST)->pad[i]);
		putc(' ');
	}
	puts("\nirq_group");      //0x080 - 0x0fc
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->irq_group[i]);
		putc(' ');
	}
	puts("\nirq_enable_set");    //0x100 - 0x17c
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->irq_enable_set[i]);
		putc(' ');
	}
	puts("\nirq_enable_clear");  //0x180 - 0x1fc
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->irq_enable_clear[i]);
		putc(' ');
	}
	puts("\nirq_pend_set");      //0x200 - 0x27c
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->irq_pend_set[i]);
		putc(' ');
	}
	puts("\nirq_pend_clear");    //0x280 - 0x2fc
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->irq_pend_clear[i]);
		putc(' ');
	}
	puts("\nirq_active_status"); //0x300 - 0x37c
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->irq_active_status[i]);
		putc(' ');
	}
	puts("\npad1");              //0x380 - 0x3fc
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->pad1[i]);
		putc(' ');
	}
	puts("\nirq_priority");    //0x400 - 0x7fb
	for(i = 0; i < 1020; i++) {
		puthex_8((GIC_DIST)->irq_priority[i]);
		putc(' ');
	}
	puts("\npad2");                  //0x7fc
	puthex_8((GIC_DIST)->pad2);
	puts("\nirq_target");      //0x800 - 0xbfb
	for(i = 0; i < 1020; i++) {
		puthex_8((GIC_DIST)->irq_target[i]);
		putc(' ');
	}
	puts("\npad3");                  //0xbfc
	puthex_32((GIC_DIST)->pad3);
	puts("\nirq_config");        //0xc00 - 0xcfc
	for(i = 0; i < 64; i++) {
		puthex_32((GIC_DIST)->irq_config[i]);
		putc(' ');
	}
	puts("\nirq_status");        //0xd00 - 0xd7c
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->irq_status[i]);
		putc(' ');
	}
	puts("\npad4");              //0xd80 - 0xdfc
	for(i = 0; i < 32; i++) {
		puthex_32((GIC_DIST)->pad4[i]);
		putc(' ');
	}
}
