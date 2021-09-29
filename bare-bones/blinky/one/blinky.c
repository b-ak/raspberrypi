/*
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 */

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include "common.h"

static inline uint32_t GPIO_FUNCTION_SELECT(uint32_t gpio)
{
	switch (gpio) {
		case 0 ... 9:
			return GPFSEL0;
		case 10 ... 19:
			return GPFSEL1;
		case 20 ... 29:
			return GPFSEL2;
		case 30 ... 39:
			return GPFSEL3;
		case 40 ... 49:
			return GPFSEL4;
		case 50 ... 53:
			return GPFSEL5;
		default:
			uart_puts("[....] I don't have record of that GPIO number u specified \r\n");	
			return 0;
	}
}	

static inline void GPIO_SET(uint32_t gpio)
{
	switch (gpio) {
		case 0 ... 31:
			__raw_writel(GPSET0, (1 << gpio));
		case 32 ... 53:
			__raw_writel(GPSET1, (1 << (gpio%32)));
	}
}

static inline void GPIO_CLR(uint32_t gpio)
{
	switch (gpio) {
		case 0 ... 31:
			__raw_writel(GPCLR0, (1 << gpio));
		case 32 ... 53:
			__raw_writel(GPCLR1, (1 << (gpio%32)));
	}
}

/*
 * @fn: Init GPIO number
 *
 * @params
 * 	gpio - configure the function select to GPIO
 *
 */ 
void gpio_init(uint32_t gpio)
{
	uint32_t reg;

	reg = __raw_readl(GPIO_FUNCTION_SELECT(gpio));
	reg &= ~(FLD_MASK << (gpio%10)*3);
	reg |= (DIR_OUT << (gpio%10)*3);
	__raw_writel(GPIO_FUNCTION_SELECT(gpio), reg);

}

void blink(uint32_t gpio)
{
	// Turn ON LED connected to GPIO @ ...
	GPIO_SET(gpio);

	delay(0x1000000);
	// Turn OFF LED connected to GPIO @ ... 
	GPIO_CLR(gpio);
	
	delay(0xf0000);
}
	
void _main(void)
{
	// Initialize UART
	uart_init();
	uart_puts("[....] Hello, Terminal!! \r\n");

	// Init GPIO to blink LED @ ...
	gpio_init(2);
	gpio_init(11);
	gpio_init(23);
	gpio_init(27);

	while (1) {
		blink(2);
		blink(11);
		blink(23);
		blink(27);
	}
}

