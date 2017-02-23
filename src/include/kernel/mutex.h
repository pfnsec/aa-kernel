#ifndef MUTEX_H
#define MUTEX_H


typedef volatile int mutex;


int  mutex_try_lock(mutex *);

void mutex_lock(mutex *);

void mutex_unlock(mutex *);


void __dmb();


#endif
