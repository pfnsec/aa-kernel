#ifndef MAILBOX_H
#define MAILBOX_H
#include "peripherals.h"


#define MAILBOX_BASE (PERIPH_BASE + 0xB880)

#define MAILBOX_READ   *(uint32_t *)(MAILBOX_BASE + 0x00)
#define MAILBOX_PEEK   *(uint32_t *)(MAILBOX_BASE + 0x10)
#define MAILBOX_SENDER *(uint32_t *)(MAILBOX_BASE + 0x14)
#define MAILBOX_STATUS *(uint32_t *)(MAILBOX_BASE + 0x18)
#define MAILBOX_CONFIG *(uint32_t *)(MAILBOX_BASE + 0x1C)
#define MAILBOX_WRITE  *(uint32_t *)(MAILBOX_BASE + 0x20)


#define MAILBOX_CHAN_PM   0
#define MAILBOX_CHAN_FB   1
#define MAILBOX_CHAN_UART 2

#define MAILBOX_FULL  (1 << 31)
#define MAILBOX_EMPTY (1 << 30)



int mailbox_try_read  (uint32_t *data, uint8_t channel);
int mailbox_try_write (uint32_t  data, uint8_t channel);

uint32_t mailbox_read_spin   (uint8_t channel);
void     mailbox_write_spin  (uint8_t channel, uint32_t data);

uint32_t mailbox_read_yield  (uint8_t channel);
void     mailbox_write_yield (uint8_t channel, uint32_t data);


#endif
