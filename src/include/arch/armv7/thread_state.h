#ifndef THREAD_STATE_H
#define THREAD_STATE_H

typedef struct thread_state_t {
	uint32_t reg[16];
} __attribute__((packed)) thread_state_t;

//typedef uint32_t thread_state_t[16];

int save_thread_state();
int load_thread_state();

extern thread_state_t *current_thread_state;

extern uint32_t get_cpsr();

extern uint32_t *sp_ld_addr, *sp_str_addr;


#endif
