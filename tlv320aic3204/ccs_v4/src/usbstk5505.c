/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 usbstk5505.c                                                            */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Functions for board setup for the TMS320C5505 USB Stick.               */
/*                                                                           */
/*****************************************************************************/
/*
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

/*
 *  Copyright 2009 by Spectrum Digital Incorporated.
 *  All rights reserved. Property of Spectrum Digital Incorporated.
 */

/*
 *  Board Setup
 *
 */

#include "usbstk5505.h"
#include "usbstk5505_gpio.h"
#include "common.h"
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  USBSTK5505_wait( delay )                                                *
 *                                                                          *
 *      Wait in a software loop for 'x' delay                               *
 *                                                                          *
 * ------------------------------------------------------------------------ */

void USBSTK5505_wait( Uint32 delay )
{
    volatile Uint32 i;
    for ( i = 0 ; i < delay ; i++ ){ };
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _waitusec( usec )                                                       *
 *                                                                          *
 *      Wait in a software loop for 'x' microseconds                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */

void USBSTK5505_waitusec( Uint32 usec )
{
    USBSTK5505_wait( (Uint32)usec * 8 );
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  _clearINTR( usec )                                                      *
 *                                                                          *
 *      Clear all pending interrupts				                        *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void USBSTK5505_clearINTR(void)
{
	asm (" BIT(ST1,#11) = #1");	// Disable interrupts
	asm (" BIT(ST3,#7) = #0");  // Clear bus error interrupts
	IFR0 = 0xFFFF;
	IFR1 = 0xFFFF;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  USBSTK5505_peripheral_reset( )                                          *
 *                                                                          *
 *      All peripherals can be reset through software						*
 * 		using the peripheral reset control register (PRCR).					*
 * 		The peripheral software reset counter register (PSRCR) 				*
 * 		controls the number of system clock cycles that a peripheral 		*
 * 		reset signal will be asserted low once activated by the bits		*
 * 		in PRCR.                                     						*
 *                                                                          *
 * ------------------------------------------------------------------------ */
 
void USBSTK5505_peripheral_reset(void)
{
	SYS_PRCNTR = 0x20;
	SYS_PRCNTRLR = 0xBB;
	
	USBSTK5505_wait(0xFF);
	
    IVPD = 0x027F; // Load interrupt vector pointer
    debug(("Reset Peripherals is complete.\n"));
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  USBSTK5505_init( )                                                      *
 *                                                                          *
 *      Setup board board functions                                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */

Int16 USBSTK5505_init( )
{
    /* Enable clocks to all peripherals */
    SYS_PCGCR1 = 0x0000;
    SYS_PCGCR2 = 0x0000;

	/* GPIO Buttons */
	USBSTK5505_GPIO_setDirection (GPIO13, GPIO_IN);
	USBSTK5505_GPIO_enable_interrupt (GPIO13);		// EXPN-Header Pin 4, Mob
	USBSTK5505_GPIO_setDirection (GPIO12, GPIO_IN);
	USBSTK5505_GPIO_enable_interrupt (GPIO12);		// EXPN-Header Pin 6, PC
	USBSTK5505_GPIO_setDirection (GPIO14, GPIO_IN);
	USBSTK5505_GPIO_enable_interrupt (GPIO14);		// EXPN-Header Pin 8, Tel
	USBSTK5505_GPIO_setDirection (GPIO15, GPIO_IN);
	USBSTK5505_GPIO_enable_interrupt (GPIO15);		// EXPN-Header Pin 10, Mode
	USBSTK5505_GPIO_setDirection (GPIO11, GPIO_IN);
	USBSTK5505_GPIO_enable_interrupt (GPIO11);		// EXPN-Header Pin 24, Vol UP
	USBSTK5505_GPIO_setDirection (GPIO5, GPIO_IN);
	USBSTK5505_GPIO_enable_interrupt (GPIO5);		// EXPN-Header Pin 28, Vol Down
	
//	IOINTEDG1 = IOINTEDG1 | (0x1FU << 11);
//	IOINTEDG1 = IOINTEDG1 | (0x01U << 5); 
	
	USBSTK5505_GPIO_setDirection (GPIO17, GPIO_OUT);	// EXPN-Header Pin 20
	USBSTK5505_GPIO_setDirection (GPIO16, GPIO_OUT);	// EXPN-Header Pin 18

	/* Enable interrupts */		
	c5505_register_irq();

	/* On board codec
	 * Configure Serial Port 0 
	 * Serial Port 0, mode 1 (I2S0 and GP[5:4]) **/
	SYS_EXBUSSEL = (SYS_EXBUSSEL & ~0x0300) | (0x01 << 8);
	// Select A20/GPIO26 as GPIO26
	SYS_EXBUSSEL = (SYS_EXBUSSEL & ~0x0020) | (0x01 << 5);
	// Select A19 to A15 modes as GPIOs 25 to 21 
	SYS_EXBUSSEL = (SYS_EXBUSSEL & ~0x001F) | (0x1F);

	/* Codec Two (Daugther Board)
	 * Configure Parallel Port 
	 * In Mode-1, switch this to Mode-6 for 6 GPIOs, I2S2, I2S3 and SPI **/
	SYS_EXBUSSEL = (SYS_EXBUSSEL & ~0x7000) | (0x06 << 12);
	/* Configure Serial Port 1
	 * Serial Port 1, mode 2 (GP[11:6]) **/
	SYS_EXBUSSEL = (SYS_EXBUSSEL & ~0x0C00) | (0x02 << 10); 
	
    return 0;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  End of usbstk5505.c                                                     *
 *                                                                          *
 * ------------------------------------------------------------------------ */
 
