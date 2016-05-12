#ifndef LOCK_H
#define LOCK_H

#include <stdint.h>


#define LOCK_SET 1
#define LOCK_FREE 0


//Absolutely, *definitely* not SMP-safe yet. Don't even try.

typedef struct yield_lock {
	uint32_t lock_set; 
	uint32_t held_id; //id of the thread that set the lock
} ylock_t;


uint32_t try_lock(ylock_t *);


#endif
