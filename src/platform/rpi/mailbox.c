#include <stdint.h>
#include "mailbox.h"
#include "kernel/thread.h"


int mailbox_try_read  (uint32_t *data, uint8_t channel) {
	uint32_t read_message;

	if(MAILBOX_STATUS & MAILBOX_EMPTY) {
		return 0;
	} else {
		
		read_message = MAILBOX_READ;
		if((read_message & 0xF) == channel) {
			*data = read_message >> 4;
			return 1;
		} else {
			return 0;
		}
	}
}


int mailbox_try_write (uint32_t  data, uint8_t channel) {
	uint32_t write_message = (data << 4) | (channel & 0xF);

	if(MAILBOX_STATUS & MAILBOX_FULL) {
		return 0;
	} else {
		MAILBOX_WRITE = write_message;
		return 1;
	}
}


uint32_t mailbox_read_spin   (uint8_t channel) {
	uint32_t data;

	while(!mailbox_try_read(&data, channel)) {
	}

	return data;
}


void mailbox_write_spin  (uint8_t channel, uint32_t data) {

	while(!mailbox_try_write(data, channel)) {
	}
}


uint32_t mailbox_read_yield  (uint8_t channel) {
	uint32_t data;

	while(!mailbox_try_read(&data, channel)) {
		yield();
	}

	return data;
}


void mailbox_write_yield (uint8_t channel, uint32_t data) {

	while(!mailbox_try_write(data, channel)) {
		yield();
	}
}
