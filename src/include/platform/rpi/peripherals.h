#ifndef PERIPHERALS_H
#define PERIPHERALS_H
#include <stdint.h>


#define PERIPH_BASE 0x20000000

#define periph_bus_addr(addr) (addr + 0x40000000)

#define periph_phy_addr(addr) (addr - 0x40000000)


#endif
