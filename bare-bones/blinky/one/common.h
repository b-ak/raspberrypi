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

#ifndef BLINKY_H
#define BLINKY_H

#define FLD_MASK 0x07
#define DIR_OUT	 0x01

enum address_map
{
    // The GPIO registers base address.
    GPIO_BASE = 0x20200000,
 
    // The offsets for reach register.
    // Controls actuation of pull up/down to ALL GPIO pins.
    GPPUD = (GPIO_BASE + 0x94),
 
    // Controls actuation of pull up/down for specific GPIO pin.
    GPPUDCLK0 = (GPIO_BASE + 0x98),
	
	// GPIO Function Select 0 (for GPIOs 0-9)
	GPFSEL0 = (GPIO_BASE + 0x0000),
	// GPIO Function Select 1 (for GPIOs 10-19)
	GPFSEL1 = (GPIO_BASE + 0x0004),
	// GPIO Function Select 2 (for GPIOs 20-29)
	GPFSEL2 = (GPIO_BASE + 0x0008),
	// GPIO Function Select 3 (for GPIOs 30-39)
	GPFSEL3 = (GPIO_BASE + 0x000C),
	// GPIO Function Select 4 (for GPIOs 40-49)
	GPFSEL4 = (GPIO_BASE + 0x0010),
	// GPIO Function Select 5 (for GPIOs 50-53)
	GPFSEL5 = (GPIO_BASE + 0x0014),

	// GPIO Pin Output Set 0 (GPIOs 0-31)
	GPSET0 = (GPIO_BASE + 0x001C),
	// GPIO Pin Output Set 1 (GPIOs 32-53)
	GPSET1 = (GPIO_BASE + 0x0020),

	// GPIO Pin Output Clear 0 (GPIOs 0-31)
	GPCLR0 = (GPIO_BASE + 0x0028),
	// GPIO Pin Output Clear 1 (GPIOs 32-53)
	GPCLR1 = (GPIO_BASE + 0x002C),
 
    // The base address for UART.
    UART0_BASE = 0x20201000,
 
    // The offsets for reach register for the UART.
    UART0_DR     = (UART0_BASE + 0x00),
    UART0_RSRECR = (UART0_BASE + 0x04),
    UART0_FR     = (UART0_BASE + 0x18),
    UART0_ILPR   = (UART0_BASE + 0x20),
    UART0_IBRD   = (UART0_BASE + 0x24),
    UART0_FBRD   = (UART0_BASE + 0x28),
    UART0_LCRH   = (UART0_BASE + 0x2C),
    UART0_CR     = (UART0_BASE + 0x30),
    UART0_IFLS   = (UART0_BASE + 0x34),
    UART0_IMSC   = (UART0_BASE + 0x38),
    UART0_RIS    = (UART0_BASE + 0x3C),
    UART0_MIS    = (UART0_BASE + 0x40),
    UART0_ICR    = (UART0_BASE + 0x44),
    UART0_DMACR  = (UART0_BASE + 0x48),
    UART0_ITCR   = (UART0_BASE + 0x80),
    UART0_ITIP   = (UART0_BASE + 0x84),
    UART0_ITOP   = (UART0_BASE + 0x88),
    UART0_TDR    = (UART0_BASE + 0x8C),
};

static inline void __raw_writel(uint32_t reg, uint32_t data)
{
	*(volatile uint32_t *)reg = data;
}
 
static inline uint32_t __raw_readl(uint32_t reg)
{
	return *(volatile uint32_t *)reg;
}
 
/* Loop <delay> times in a way that the compiler won't optimize away. */
static inline void delay(int32_t count)
{
	asm volatile("__delay_%=: subs %[count], %[count], #1; bne __delay_%=\n"
		 : : [count]"r"(count) : "cc");
}

void uart_puts(const char* str);
void uart_putc(unsigned char byte);
unsigned char uart_getc(void);
void uart_init(void);
void uart_write(const unsigned char* buffer, size_t size);

#endif

