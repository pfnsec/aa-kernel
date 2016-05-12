#ifndef GPIO_H
#define GPIO_H 
#include <stdint.h>
#include "peripherals.h"

//GPIO Function Select
#define GPIO_FSEL0 (uint32_t *)(PERIPH_BASE + 0x00200000)
#define GPIO_FSEL1 (uint32_t *)(PERIPH_BASE + 0x00200004)
#define GPIO_FSEL2 (uint32_t *)(PERIPH_BASE + 0x00200008)
#define GPIO_FSEL3 (uint32_t *)(PERIPH_BASE + 0x002000C0)
#define GPIO_FSEL4 (uint32_t *)(PERIPH_BASE + 0x00200010)
#define GPIO_FSEL5 (uint32_t *)(PERIPH_BASE + 0x00200014)


//GPIO Output Set
#define GPIO_SET0  (uint32_t *)(PERIPH_BASE + 0x0020001C)
#define GPIO_SET1  (uint32_t *)(PERIPH_BASE + 0x00200020)


//GPIO Output Clear
#define GPIO_CLR0  (uint32_t *)(PERIPH_BASE + 0x00200028)
#define GPIO_CLR1  (uint32_t *)(PERIPH_BASE + 0x0020002C)

#define GPIO_PIN_INPUT  0
#define GPIO_PIN_OUTPUT 1

#define GPIO_LED_ACT    16

void gpio_pin_function(int pin, int function);

void blink_init();

void blink();

#endif
