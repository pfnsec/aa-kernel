#ifndef THREAD_STATE_H
#define THREAD_STATE_H

#if ARCH == armv7

typedef struct thread_state_t {
	uint32_t reg[16];
} __attribute__((packed)) thread_state_t;

#elif ARCH == armv8

typedef struct thread_state_t {
	uint32_t reg[32];
} __attribute__((packed)) thread_state_t;

#endif


int save_thread_state();
int load_thread_state();

extern uint32_t *current_thread_state;

#endif
