/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/*   aic3204_init.c                                                          */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Initialisation of the AIC3204 Codec.                                    */
/*                                                                           */
/*   Sets up the codec for line inputs.                                      */
/*   Uses a sampling frequency of 44100 Hz.                                  */
/*   Note: "aic3204.h" needs to go after "usbstk5505.h"                      */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00                                                          */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*                                                                           */
/*   Revision 1.00                                                           */
/*   20th December 2009. Created by Richard Sikora from Texas Instruments    */
/*                       code. The crystal on the USB board has been changed */
/*                       from an earlier release and therefore some register */
/*                       values below also needed to be modified.            */
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


#include "usbstk5505.h"
#include "aic3204.h"
#include "stdio.h"
#include "common.h"

/* Setup: Line input. Fs = 44100 Hz */

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  AIC3204 Initialisation of both sampling frequency and gain in dB.       *
 *      Initialise both the registers and I2S                               *
 *                                                                          *
 * ------------------------------------------------------------------------ */

unsigned long set_sampling_frequency_and_gain(unsigned long SamplingFrequency, unsigned int ADCgain, CODEC_SEL type)
{
	unsigned int PLLPR = 0x91; // Default to 44100 Hz
	unsigned int gain;
	unsigned long output;

	if ( ADCgain >= 48)
	{
		gain = 95;      //  Limit gain to 47.5 dB
		ADCgain = 48;   // For display using printf()
	}
	else
	{
		gain = (ADCgain << 1); // Convert 1dB steps to 0.5dB steps
	}

	switch (SamplingFrequency)
	{
		case 48000:
			PLLPR = 0x91; // 1001 0001b. PLL on. P = 1, R = 1.
			debug(("Sampling frequency 48000 Hz Gain = %2d dB\n", ADCgain));
			output = 48000;
			break;

		case 44100:
			PLLPR = 0x91; // 1001 0001b. PLL on. P = 1, R = 1.
			debug(("Sampling frequency 44100 Hz Gain = %2d dB\n", ADCgain));
			output = 44100;
			break;

		case 16000:
			PLLPR = 0xB1; // 1011 0001b. PLL on. P = 3, R = 1.
			debug(("Sampling frequency 16000 Hz Gain = %2d dB\n", ADCgain));
			output = 16000;
			break;

		case 12000:
			PLLPR = 0xC1; //1100 0001b. PLL on. P = 4, R = 1.
			debug(("Sampling frequency 12000 Hz Gain = %2d dB\n", ADCgain));
			output = 12000;
			break;

		case 9600:
			PLLPR = 0xD1; //1101 0001b. PLL on. P = 5, R = 1.
			debug(("Sampling frequency 9600 Hz Gain = %2d dB\n", ADCgain));
			output = 9600;
			break;

		case 8000:
			PLLPR = 0xE1; //1110 0001b. PLL on. P = 6, R = 1.
			debug(("Sampling frequency 8000 Hz Gain = %2d dB\n", ADCgain));
			output = 8000;
			break;

		case 6857:
			PLLPR = 0xF1; //1111 0001b. PLL on. P = 7, R = 1.
			debug(("Sampling frequency 6857 Hz Gain = %2d dB\n", ADCgain));
			output = 6857;
			break;

		default:
			PLLPR = 0x91; // 1001 0001b. PLL on. P = 1, R = 1.
			debug(("Sampling frequency not recognised. Default to 44100 Hz Gain = %2d dB\n", ADCgain));
			output = 44100;
			break;
	}

	if(type == CODEC_ONE)
	{
		/* Configure AIC3204 */
		AIC3204_rset( 0, 0 );      // Select page 0
		AIC3204_rset( 1, 1 );      // Reset codec
		AIC3204_rset( 0, 1 );      // Point to page 1
		AIC3204_rset( 1, 8 );      // Disable crude AVDD generation from DVDD
		AIC3204_rset( 2, 1 );      // Enable Analog Blocks, use LDO power
		AIC3204_rset( 0, 0 );      // Select page 0

		/* PLL and Clocks config and Power Up  */
#ifdef DSP_MODE
		AIC3204_rset( 27, 0x4C );
		AIC3204_rset( 28, 0x01 );  // Data ofset = 0
#else
		AIC3204_rset( 27, 0x1D );  // BCLK and WCLK is set as o/p to AIC3204(Master)
		AIC3204_rset( 28, 0x00 );  // Data ofset = 0
#endif
		// fs = 48kHz
		AIC3204_rset( 4, 3 );      // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
		AIC3204_rset( 6, 7 );      // PLL setting: J
		AIC3204_rset( 7, 0x06 );   // PLL setting: HI_BYTE(D)
		AIC3204_rset( 8, 0x90 );   // PLL setting: LO_BYTE(D)

		// PRB_P2 and PRB_R2 selected
		AIC3204_rset( 60, 0x02 );  // DAC, Stereo, 48KHz, Highest Performance, DOSR = 128
		AIC3204_rset( 61, 0x02 );  // ADC, Stereo, 48KHz, Highest Performance, AOSR = 128

		// For 32 bit clocks per frame in Master mode ONLY
		AIC3204_rset( 30, 0x88 );     // For 32 bit clocks per frame in Master mode ONLY
                             		  // BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
		AIC3204_rset( 5, PLLPR );  // PLL setting: Power up PLL, P=1 and R=1

		AIC3204_rset( 13, 0 );     // Hi_Byte(DOSR) for DOSR = 0 decimal or 0x00 DAC oversampling
		AIC3204_rset( 14, 0x80 );  // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
		AIC3204_rset( 20, 0x80 );  // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
		AIC3204_rset( 11, 0x82 );  // Power up NDAC and set NDAC value to 
		AIC3204_rset( 12, 0x87 );  // Power up MDAC and set MDAC value to 
		AIC3204_rset( 18, 0x87 );  // Power up NADC and set NADC value to 
		AIC3204_rset( 19, 0x82 );  // Power up MADC and set MADC value to 

		/* DAC ROUTING and Power Up */
		AIC3204_rset( 0, 1 );      // Select page 1
		AIC3204_rset( 12, 8 );     // LDAC AFIR routed to HPL
		AIC3204_rset( 13, 8 );     // RDAC AFIR routed to HPR
		AIC3204_rset( 0, 0 );      // Select page 0

		AIC3204_rset( 64, 2 );         // Left vol=right vol
		AIC3204_rset( 65, 0x30 );      // Left DAC gain to +24 dB VOL; Right tracks Left
		AIC3204_rset( 63, 0xd4 );      // Power up left,right data paths and set channel

#ifdef USE_DRC

		// DRC
		AIC3204_rset( 60, 1 );   // DAC programming block enable
		AIC3204_rset( 61, 1 );   // ADC programming block enable

		// DRC
		AIC3204_rset( 68, 0x75 );  // DAC => DRC Enabled for both channels, Threshold = -24 db, Hysteresis = 3 dB
		AIC3204_rset( 69, 0x00 );  // DRC Hold = 0 ms, Rate of Changes of Gain = 0.5 dB/Fs
		AIC3204_rset( 70, 0xB6 );  // Attack Rate = 1.9531e-4 dB/Frame , DRC Decay Rate =2.4414e-5 dB/Frame

		AIC3204_rset( 0, 0x2E );   // Page 46

		AIC3204_rset( 52, 0x7F );    //DRC HPF
		AIC3204_rset( 53, 0xAB );    //DRC HPF
		AIC3204_rset( 54, 0x00 );    //DRC HPF
		AIC3204_rset( 55, 0x00 );    //DRC HPF
		AIC3204_rset( 56, 0x80 );    //DRC HPF
		AIC3204_rset( 57, 0x55 );    //DRC HPF
		AIC3204_rset( 58, 0x00 );    //DRC HPF
		AIC3204_rset( 59, 0x00 );    //DRC HPF
		AIC3204_rset( 60, 0x7F );    //DRC HPF
		AIC3204_rset( 61, 0x56 );    //DRC HPF
		AIC3204_rset( 62, 0x00 );    //DRC HPF
		AIC3204_rset( 63, 0x00 );    //DRC HPF

		AIC3204_rset( 64, 0x00 );   //DRC LPF
		AIC3204_rset( 65, 0x11 );   //DRC LPF
		AIC3204_rset( 66, 0x00 );   //DRC LPF
		AIC3204_rset( 67, 0x00 );   //DRC LPF
		AIC3204_rset( 68, 0x00 );   //DRC LPF
		AIC3204_rset( 69, 0x11 );   //DRC LPF
		AIC3204_rset( 70, 0x00 );   //DRC LPF
		AIC3204_rset( 71, 0x00 );   //DRC LPF
		AIC3204_rset( 72, 0x7F );   //DRC LPF
		AIC3204_rset( 73, 0xDE );   //DRC LPF
		AIC3204_rset( 74, 0x00 );   //DRC LPF
		AIC3204_rset( 75, 0x00 );   //DRC LPF
#endif

		AIC3204_rset( 0, 1 );      // Select page 1
		AIC3204_rset( 16, 5 );     // Unmute HPL , 5dB gain
		AIC3204_rset( 17, 5 );     // Unmute HPR , 5dB gain
		AIC3204_rset( 9, 0x30 );   // Power up HPL,HPR
		AIC3204_rset( 0, 0 );      // Select page 0
		USBSTK5505_wait( 100 );    // wait

		/* ADC ROUTING and Power Up */
		AIC3204_rset( 0, 1 );         // Select page 1
		AIC3204_rset( 10, 0x40 );	  // Common Mode is 0.75V
		AIC3204_rset( 51, 0x68 );     // Power up MICBIAS with LDOIN (0x48). MICBIAS = 2.075V(CM = 0.75V)
		AIC3204_rset( 52, 0x10 );     // STEREO 1 Jack

		// IN2_L to LADC_P through 0 kohm
		AIC3204_rset( 55, 0x10 );     // IN2_R to RADC_P through 0 kohmm
		AIC3204_rset( 54, 1 );        // CM_1 (common mode) to LADC_M through 0 kohm
		AIC3204_rset( 57, 0x40 );     // CM_1 (common mode) to RADC_M through 0 kohm
		AIC3204_rset( 59, gain );     // MIC_PGA_L unmute
		AIC3204_rset( 60, gain );     // MIC_PGA_R unmute

		AIC3204_rset( 0, 0 );        // Select page 0
		AIC3204_rset( 81, 0xc0 );    // Powerup Left and Right ADC
		AIC3204_rset( 82, 0 );       // Unmute Left and Right ADC

#ifdef USE_AGC
		// AGC
		AIC3204_rset( 83, 0x14 );  // Left ADC Channel Volume Control Register 10dB
		AIC3204_rset( 86, 0xA0 );  // Enable AGC, set Target gain = –10 dB
		AIC3204_rset( 87, 0x7E );  // set hysteresis = 2 dB, Noise threshold = –90 dB
		AIC3204_rset( 88, 0x50 );  // set Maximum gain = 40 dB
		AIC3204_rset( 89, 0x08 );  // set attack time = 20 ms
		AIC3204_rset( 90, 0x32 );  // Decay time = 500 ms
		AIC3204_rset( 91, 0x00 );  // Noise debounce time = 0 ms
		AIC3204_rset( 92, 0x06 );  // signal debounce time = 2 ms
		AIC3204_rset( 93, 0x14 );  // Left Channel AGC Control Register 10dB
#endif

		AIC3204_rset( 0, 0 );    // Select page 0
		USBSTK5505_wait( 100 );  // Wait
	}

	/* CODEC 2 Is on the SPI Bus */
	else if(type == CODEC_TWO) // Off board codec is oconnected with SPI
	{

		/* Configure AIC3204 */
		AIC3204_II_rset( 0, 0 );      // Select page 0
		AIC3204_II_rset( 1, 1 );      // Reset codec
		AIC3204_II_rset( 0, 1 );      // Point to page 1
		AIC3204_II_rset( 1, 8 );      // Disable crude AVDD generation from DVDD
		AIC3204_II_rset( 2, 1 );      // Enable Analog Blocks, use LDO power
		AIC3204_II_rset( 0, 0 );      // Select page 0

		/* PLL and Clocks config and Power Up  */
#ifdef DSP_MODE
		AIC3204_II_rset( 27, 0x4C );
		AIC3204_II_rset( 28, 0x01 );  // Data ofset = 0
#else
		AIC3204_II_rset( 27, 0x1D );  // BCLK and WCLK is set as o/p to AIC3204(Master)
		AIC3204_II_rset( 28, 0x00 );  // Data ofset = 0
#endif
		// fs = 48kHz
		AIC3204_II_rset( 4, 3 );      // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
		AIC3204_II_rset( 6, 7 );      // PLL setting: J
		AIC3204_II_rset( 7, 0x06 );   // PLL setting: HI_BYTE(D)
		AIC3204_II_rset( 8, 0x90 );   // PLL setting: LO_BYTE(D)

		// PRB_P25 for Beep Generator and PRB_R2 selected
		AIC3204_II_rset( 60, 0x19 );  // DAC, Stereo, 48KHz, Highest Performance, DOSR = 128
		AIC3204_II_rset( 61, 0x02 );  // ADC, Stereo, 48KHz, Highest Performance, AOSR = 128

		// For 32 bit clocks per frame in Master mode ONLY
		AIC3204_II_rset( 30, 0x88 );  // For 32 bit clocks per frame in Master mode ONLY
                               		  // BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
		AIC3204_II_rset( 5, PLLPR );  // PLL setting: Power up PLL, P=1 and R=1

		AIC3204_II_rset( 13, 0 );     // Hi_Byte(DOSR) for DOSR = 0 decimal or 0x00 DAC oversampling
		AIC3204_II_rset( 14, 0x80 );  // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
		AIC3204_II_rset( 20, 0x80 );  // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6

		AIC3204_II_rset( 11, 0x82 );  // Power up NDAC and set NDAC value to 
		AIC3204_II_rset( 12, 0x87 );  // Power up MDAC and set MDAC value to 
		AIC3204_II_rset( 18, 0x87 );  // Power up NADC and set NADC value to 
		AIC3204_II_rset( 19, 0x82 );  // Power up MADC and set MADC value to 

		/* DAC ROUTING and Power Up */
		AIC3204_II_rset( 0, 1 );      // Select page 1
		AIC3204_II_rset( 12, 8 );     // LDAC AFIR routed to HPL
		AIC3204_II_rset( 13, 8 );     // RDAC AFIR routed to HPR

 		// Avoid initial Hiss. Reduce N to decrease startup delay
 		// Pop sound increases as N reduces		
		AIC3204_II_rset( 20, 0x14);
		AIC3204_II_rset( 0, 0 );      // Select page 0

		AIC3204_II_rset( 64, 2 );         // Left vol=right vol
		AIC3204_II_rset( 65, 0xdc );      // Left DAC gain to -18 dB VOL; Right tracks Left
		AIC3204_II_rset( 63, 0xd4 );      // Power up left,right data paths and set channel

#ifdef USE_DRC

		// DRC
		AIC3204_II_rset( 60, 1 );   // DAC programming block enable
		AIC3204_II_rset( 61, 1 );   // ADC programming block enable

		// DRC
		AIC3204_II_rset( 68, 0x75 );  // DAC => DRC Enabled for both channels, Threshold = -24 db, Hysteresis = 3 dB
		AIC3204_II_rset( 69, 0x00 );  // DRC Hold = 0 ms, Rate of Changes of Gain = 0.5 dB/Fs
		AIC3204_II_rset( 70, 0xB6 );  // Attack Rate = 1.9531e-4 dB/Frame , DRC Decay Rate =2.4414e-5 dB/Frame

		AIC3204_II_rset( 0, 0x2E );   // Page 46

		AIC3204_II_rset( 52, 0x7F );    //DRC HPF
		AIC3204_II_rset( 53, 0xAB );    //DRC HPF
		AIC3204_II_rset( 54, 0x00 );    //DRC HPF
		AIC3204_II_rset( 55, 0x00 );    //DRC HPF
		AIC3204_II_rset( 56, 0x80 );    //DRC HPF
		AIC3204_II_rset( 57, 0x55 );    //DRC HPF
		AIC3204_II_rset( 58, 0x00 );    //DRC HPF
		AIC3204_II_rset( 59, 0x00 );    //DRC HPF
		AIC3204_II_rset( 60, 0x7F );    //DRC HPF
		AIC3204_II_rset( 61, 0x56 );    //DRC HPF
		AIC3204_II_rset( 62, 0x00 );    //DRC HPF
		AIC3204_II_rset( 63, 0x00 );    //DRC HPF

		AIC3204_II_rset( 64, 0x00 );   //DRC LPF
		AIC3204_II_rset( 65, 0x11 );   //DRC LPF
		AIC3204_II_rset( 66, 0x00 );   //DRC LPF
		AIC3204_II_rset( 67, 0x00 );   //DRC LPF
		AIC3204_II_rset( 68, 0x00 );   //DRC LPF
		AIC3204_II_rset( 69, 0x11 );   //DRC LPF
		AIC3204_II_rset( 70, 0x00 );   //DRC LPF
		AIC3204_II_rset( 71, 0x00 );   //DRC LPF
		AIC3204_II_rset( 72, 0x7F );   //DRC LPF
		AIC3204_II_rset( 73, 0xDE );   //DRC LPF
		AIC3204_II_rset( 74, 0x00 );   //DRC LPF
		AIC3204_II_rset( 75, 0x00 );   //DRC LPF
#endif     

		/* ADC ROUTING and Power Up */
		AIC3204_II_rset( 0, 1 );         // Select page 1
		AIC3204_II_rset( 51, 0x48 );     // power up MICBIAS with AVDD (0x40)or LDOIN (0x48)
		AIC3204_II_rset( 52, 0x10 );     // STEREO 1 Jack

		// IN2_L to LADC_P through 0 kohm
		AIC3204_II_rset( 55, 0x10 );     // IN2_R to RADC_P through 0 kohmm
		AIC3204_II_rset( 54, 1 );        // CM_1 (common mode) to LADC_M through 0 kohm
		AIC3204_II_rset( 57, 0x40 );     // CM_1 (common mode) to RADC_M through 0 kohm
		AIC3204_II_rset( 59, gain );     // MIC_PGA_L unmute
		AIC3204_II_rset( 60, gain );     // MIC_PGA_R unmute

		AIC3204_II_rset( 0, 0 );        // Select page 0
		AIC3204_II_rset( 81, 0xc0 );    // Powerup Left and Right ADC
		AIC3204_II_rset( 82, 0 );       // Unmute Left and Right ADC

#ifdef USE_AGC
		// AGC
		AIC3204_II_rset( 83, 0x14 );  // Left ADC Channel Volume Control Register 10dB
		AIC3204_II_rset( 86, 0xA0 );  // Enable AGC, set Target gain = –10 dB
		AIC3204_II_rset( 87, 0x7E );  // set hysteresis = 2 dB, Noise threshold = –90 dB
		AIC3204_II_rset( 88, 0x50 );  // set Maximum gain = 40 dB
		AIC3204_II_rset( 89, 0x08 );  // set attack time = 20 ms
		AIC3204_II_rset( 90, 0x32 );  // Decay time = 500 ms
		AIC3204_II_rset( 91, 0x00 );  // Noise debounce time = 0 ms
		AIC3204_II_rset( 92, 0x06 );  // signal debounce time = 2 ms
		AIC3204_II_rset( 93, 0x14 );  // Left Channel AGC Control Register 10dB
#endif

		AIC3204_II_rset( 0, 1 );      // Select page 1
		AIC3204_II_rset( 16, 5 );     // Unmute HPL , 5dB gain
		AIC3204_II_rset( 17, 5 );     // Unmute HPR , 5dB gain
		AIC3204_II_rset( 9, 0x30 );   // Power up HPL,HPR
		AIC3204_II_rset( 0, 0 );      // Select page 0
		USBSTK5505_wait( 10 );  	  // Wait

	}


	if(type == CODEC_TWO)
	{
		I2S2_SRGR = 0x0;
#ifdef DSP_MODE
		I2S2_CR = 0x8011;    // 16-bit word, slave, enable DSP_MODE
#else
		I2S2_CR = 0x8010;    // 16-bit word, slave, enable I2S
#endif
		I2S2_ICMR = 0x3f;    // Enable interrupts
	}

	else if (type == CODEC_ONE)
	{
		/* I2S0 settings */
		I2S0_SRGR = 0x0;
#ifdef DSP_MODE
		I2S0_CR = 0x8011;    // 16-bit word, slave, enable DSP_MODE
#else
		I2S0_CR = 0x8010;    // 16-bit word, slave, enable I2S
#endif
		I2S0_ICMR = 0x3f;    // Enable interrupts
	}

	return(output);
}


/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Beep generator		                                                    *
 *                                                                          *
 * ------------------------------------------------------------------------ */
 void beep_generator(BEEP_TYPE type)
 {
 	volatile Uint8 i;
 	if ((type == VOL_MAX) || (type == VOL_UP)) {
	 	for (i=0; i<=3; i++) {
			 	AIC3204_II_rset(0, 0);
			 	AIC3204_II_rset(73, 0x00);
			 	AIC3204_II_rset(74, 0x0B);
			 	AIC3204_II_rset(75, 0x40);
			 	AIC3204_II_rset(76, 0x07);
			 	AIC3204_II_rset(77, 0x89);
			 	AIC3204_II_rset(78, 0x7F);
			 	AIC3204_II_rset(79, 0xC7);
			 	AIC3204_II_rset(72, 0x63); // Right channel Beep volume = Left channel, at - 35 dB
			 	USBSTK5505_wait(100);
			 	
			 	AIC3204_II_rset(71, 0x80); // Enable Beep Generator
			 	USBSTK5505_wait(100);
			 	
			 	if (type == VOL_UP)
			 		return;
	 	}
 	} else {
		for (i=0; i<=3; i++) {	 	
		 		AIC3204_II_rset(0, 0);
			 	AIC3204_II_rset(73, 0x00);
			 	AIC3204_II_rset(74, 0x0B);
			 	AIC3204_II_rset(75, 0x40);
			 	AIC3204_II_rset(76, 0x05);
			 	AIC3204_II_rset(77, 0xDD);
			 	AIC3204_II_rset(78, 0x7F);
			 	AIC3204_II_rset(79, 0xDE);
			 	AIC3204_II_rset(72, 0x63);
			 	USBSTK5505_wait(100);
			 	
			 	AIC3204_II_rset(71, 0x80);
			 	USBSTK5505_wait(100);
			 	
			 	if (type == VOL_DOWN)
			 		return;
		}
 	}
}
 	
/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  End of aic3204_init.c                                                   *
 *                                                                          *
 * ------------------------------------------------------------------------ */






