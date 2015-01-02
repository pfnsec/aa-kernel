#ifndef PLATFORM_H
#define PLATFORM_H
#include "config.h"

#if (PLATFORM == integratorcp)  || (PLATFORM == virt)
	#define CONSOLE PL011
#endif
	#define CONSOLE PL011

#endif
