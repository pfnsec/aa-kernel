#ifndef PLATFORM_H
#define PLATFORM_H
#include "config.h"

#ifndef BOOT_CON
#define BOOT_CON UART0
#endif

#define MEM_BEGIN &_seg_data
#define MEM_END (MEM_BEGIN + 0x04000000)

#endif
