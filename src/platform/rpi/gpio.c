#include <stdint.h>
#include "gpio.h"



void gpio_pin_function(int pin, int function) {
	uint32_t pin_bitfield = (7 << ((pin % 10) * 3));
	uint32_t fun_bitfield = (function << ((pin % 10) * 3));


	if(pin > 52) 
		return;

	if(pin < 10) {
		*(GPIO_FSEL0) = (*(GPIO_FSEL0) & ~pin_bitfield) | fun_bitfield;
	} else if (pin < 20) {
		*(GPIO_FSEL1) = (*(GPIO_FSEL1) & ~pin_bitfield) | fun_bitfield;
	} else if (pin < 30) {
		*(GPIO_FSEL2) = (*(GPIO_FSEL2) & ~pin_bitfield) | fun_bitfield;
	} else if (pin < 40) {
		*(GPIO_FSEL3) = (*(GPIO_FSEL3) & ~pin_bitfield) | fun_bitfield;
	} else if (pin < 50) {
		*(GPIO_FSEL4) = (*(GPIO_FSEL4) & ~pin_bitfield) | fun_bitfield;
	} else {
		*(GPIO_FSEL5) = (*(GPIO_FSEL5) & ~pin_bitfield) | fun_bitfield;
	}
}


void gpio_set(int pin) {

	if(pin > 52)
		return;

	if(pin < 31) {
		*(GPIO_SET0) = (uint32_t)(1 << pin);
	} else {
		*(GPIO_SET1) = (uint32_t)(1 << (pin - 32));
	}
}


void gpio_clear(int pin) {
	if(pin > 52)
		return;

	if(pin < 31) {
		*(GPIO_CLR0) = (uint32_t)(1 << pin);
	} else {
		*(GPIO_CLR1) = (uint32_t)(1 << (pin - 32));
	}
}



void blink_init() {
	*(GPIO_FSEL1) = (*(GPIO_FSEL1) & (7 << 18)) | (1 << 18);
//	gpio_pin_function(GPIO_LED_ACT, GPIO_PIN_OUTPUT);
	gpio_clear(GPIO_LED_ACT);
}


void blink() {
	const int period = 1000000;
	volatile int i     = 0;
	int state = 0;
	while(1) {
		for(i = 0; i < period; i++);

		i = 0;
		gpio_clear(GPIO_LED_ACT);
		yield();

		for(i = 0; i < period; i++);

		i = 0;
		gpio_set  (GPIO_LED_ACT);
		yield();
	}
}
