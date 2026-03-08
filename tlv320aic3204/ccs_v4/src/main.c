
/*****************************************************************************/
/*                                                                           */
/* PROJECT                                                                   */
/*   IIRFilters                                                              */
/*                                                                           */
/* FILENAME                                                                  */
/* 	 main.c                                                                  */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Finite Impulse Response (IIR) Filters.                                  */
/*   Low pass and high pass filters. Audio line in / audio headphones out.   */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*                                                                           */
/*   Revision 1.00   Richard Sikora                                          */
/*   5th March 2010. Original template code from Spectrum Digital.           */
/*                                                                           */
/*   Revision 1.01   Richard Sikora                                          */
/*   10th August 2010. Converted to use CSL                                  */
/*                                                                           */
/*****************************************************************************/
/*
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

#include "stdio.h"
#include "usbstk5505.h"
#include "PLL.h"
#include <stdlib.h>
#include <stdint.h>
#include "common.h"
#include "aic3204.h"
#include "IIR_band_pass_filters.h"
//#include "IIR_band_stop_filters.h"
#include "IIR_filters_fourth_order.h"
//#include "IIR_low_pass_filters.h"
//#include "IIR_high_pass_filters.h"

#define SAMPLES_PER_SECOND 44100
#define GAIN_IN_dB  0

Int16 left_input;
Int16 right_input;
Int16 left_output;
Int16 right_output;
Int16 mono_input;
Int16 left_input1;
Int16 right_input1;
Int16 left_output1;
Int16 right_output1;

unsigned long int delay = 0;
unsigned int frequency;

Int32 *op;

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  main( )                                                                 *
 *                                                                          *
 * ------------------------------------------------------------------------ */
void main( void )
{

	/* Initialize BSL */
	USBSTK5505_peripheral_reset();
	USBSTK5505_init( );

	/* Initialize the Phase Locked Loop in EEPROM */
	pll_frequency_setup(100);

	/* Initialise hardware interface and I2C for code */
	aic3204_hardware_init(CODEC_ONE);
	aic3204_hardware_init(CODEC_TWO);

	/* Initialise the AIC3204 codec */
	/* Set sampling frequency in Hz and ADC gain in dB */
	set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB, CODEC_ONE);
	set_sampling_frequency_and_gain(SAMPLES_PER_SECOND, GAIN_IN_dB, CODEC_TWO);

	ST1_55 = (ST1_55 & ~0x2000) | (0x1 << 13); // Set XF bit, Turn On LED


#ifdef PASS_THROUGH
	// ST1_55 = (ST1_55 & ~0x2000); // Clear XF bit, Turn Off LED
	/* for (delay = 0; delay <= 770000; delay ++) */ 
	while (1) {
			aic3204_codec_read(&left_input, &right_input, CODEC_ONE);
			// Directly connect inputs to outputs for reference.
			aic3204_codec_write(left_input, right_input, CODEC_ONE);
	
			aic3204_codec_read(&left_input1, &right_input1, CODEC_TWO);
			// Directly connect inputs to outputs for reference.
			aic3204_codec_write(left_input1, right_input1, CODEC_TWO);			
	}
#endif

	asm (" BIT(ST1,#ST1_XF) = #1"); // Turn On LED

	while (1) {
		aic3204_codec_read(&left_input, &right_input, CODEC_ONE); // Configured for one interrupt per two channels.
		//left_output = fourth_order_IIR_direct_form_I_codec1 (&IIR_band_pass_300Hz_to_3300Hz[0], left_input);   ////

		aic3204_codec_read(&left_input1, &right_input1, CODEC_TWO); // Configured for one interrupt per two channels.
		op = fourth_order_IIR_direct_form_I_codec1 (&IIR_band_pass_300Hz_to_3300Hz[0], left_input, left_input1);

		left_output = op[0];
		left_output1 = op[1];

		aic3204_codec_write (left_output, left_output, CODEC_ONE);
		aic3204_codec_write (left_output1, left_output1, CODEC_TWO);	
	}

	/* Disable I2S and put codec into reset */
	aic3204_disable(CODEC_ONE);
	aic3204_disable(CODEC_TWO);

	debug(( "\n***Program has Terminated***\n" ));
	SW_BREAKPOINT;
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  End of main.c                                                           *
 *                                                                          *
 * ------------------------------------------------------------------------ */

