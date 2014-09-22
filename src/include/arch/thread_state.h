#ifndef THREAD_STATE_H
#define THREAD_STATE_H

#if ARCH == ARMv7

typedef struct thread_state_t {
} thread_state_t;

#elif ARCH == ARMv8

typedef struct thread_state_t {
} thread_state_t;

#endif


int save_thread_state(thread_state_t *);
int load_thread_state(thread_state_t *);


#endif
