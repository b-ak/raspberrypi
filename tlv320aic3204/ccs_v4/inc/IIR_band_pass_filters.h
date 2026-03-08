/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 IIR_band_pass_filters.h                                                 */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR band pass filters.                                  */
/*   Filters have been designed in two different ways:                       */
/*                                                                           */
/*   1. Using bilinear transform (BLT) from Butterworth filter.              */
/*   2. By placing poles and zeroes.                                         */
/*                                                                           */
/*   The order of the coefficients is B0, B1/2, B2, A0, A1/2, A2, where      */
/*   B0, B1/2 and B2 are the numerator coefficients, A0, A1/2 and A2 are     */
/*   the denominator coefficients.                                           */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision 1.00                                                           */
/*   29th November 2002. Created by Richard Sikora.                          */
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


#ifndef IIR_BAND_PASS_H
#define IIR_BAND_PASS_H


/*****************************************************************************/
/* Bandpass filters designed using Bilinear Transform (BLT)                  */
/*****************************************************************************/

/* Second order band pass filter 2000 Hz to 2800 Hz (nominally 2400 Hz) */
const signed int IIR_band_pass_2000Hz_to_2800Hz[6] = {  1632,      0, -1632, 
                                                      32767, -29652, 29503 };
                                                      
const signed int IIR_band_pass_300Hz_to_3300Hz[6] = {  9797,      0, -9797, 
                                                      32767, -22736, 13173 };
/* Second order band pass filter 600 Hz to 1.2 kHz */
const signed int IIR_band_pass_600Hz_to_1200Hz[6] =  {  1239,      0, -1239, 
                                                      32767, -31334, 30289 };

/* Second order band pass filter 1.2 kHz to 2.4 kHz */
const signed int IIR_band_pass_1200Hz_to_2400Hz[6] = {  2408,      0, -2408, 
                                                      32767, -29617, 27950 };

/* Second order band pass filter 2.4 kHz to 4.8 kHz */
const signed int IIR_band_pass_2400Hz_to_4800Hz[6] = {  4480,      0, -4480, 
                                                      32767, -25518, 23807 };
                                                      
/* Second order band pass filter 4.8 kHz to 9.6 kHz */
const signed int IIR_band_pass_4800Hz_to_9600Hz[6] = {  8036,      0, -8036,
                                                      32767, -15285, 16695 };

/* Second order band pass filter 600 Hz to 2.4 kHz */
const signed int IIR_band_pass_600Hz_to_2400Hz[6] = {   3468,      0, -3468,
                                                      32767, -28937, 25832 };

/* Second order band pass filter 1.2 kHz to 4.8 kHz */
const signed int IIR_band_pass_1200Hz_to_4800Hz[6] = {  6344,      0,  -6344, 
                                                      32767, -25106, 20080 };

/* Second order band pass filter 2.4 kHz to 9.6 kHz */
const signed int IIR_band_pass_2400Hz_to_9600Hz[6] = { 11060,      0, -11060, 
                                                      32767, -17227, 10647 };

/*****************************************************************************/
/* Bandpass filters designed by placing poles and zeroes.                    */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Different frequency notch filters using r = 0.9372.                       */
/*                                                                           */
/*****************************************************************************/

/* 300 Hz bandpass. w = 2.25 degrees. r = 0.9372 */
const signed int IIR_band_pass_300Hz_r_9372[6] =  {  2048,      0,  -2048, 
                                                   32767, -30686, 28781 };

/* 600 Hz bandpass. w = 4.5 degrees. r = 0.9372 */
const signed int IIR_band_pass_600Hz_r_9372[6] =  {  2048,     0,  -2048, 
                                                   32767, -30615, 28781 };

/* 1.2 kHz bandpass. w = 9.0 degrees. r = 0.9372 */
const signed int IIR_band_pass_1200Hz_r_9372[6] = {  2048,     0,  -2048, 
                                                   32767, -30331, 28781 };

/* 2.4 kHz bandpass. w = 18 degrees. r = 0.9372 */
const signed int IIR_band_pass_2400Hz_r_9372[6] = {  2048,      0,  -2048, 
                                                   32767, -29206,  28781 };

/* 4.8 kHz bandpass. w = 36 degrees. r = 0.9372 */
const signed int IIR_band_pass_4800Hz_r_9372[6] = {  2048,      0,  -2048, 
                                                   32767, -24844,  28781 };

/* 9.6 kHz bandpass. w = 72 degrees. r = 0.9372 */
const signed int IIR_band_pass_9600Hz_r_9372[6] = {  2048,     0,  -2048, 
                                                   32767, -9490,  28781  };

/*****************************************************************************/
/* 2.4 kHz bandpass filters using different values of r.                     */
/*****************************************************************************/

/* 2.4 kHz bandpass. w = 18 degrees. r = 1.00 */
const signed int IIR_band_pass_2400Hz_1_r_00[6] = { 1024,      0, -1024, 
                                                   32767, -31163, 32767 };

/* 2.4 kHz bandpass. w = 18 degrees. r = 0.97 */
const signed int IIR_band_pass_2400Hz_r_97[6] = {  1024,      0, -1024, 
                                                 32767, -30228,  30830 };

/* 2.4 kHz bandpass. w = 18 degrees. r = 0.95 */
const signed int IIR_band_pass_2400Hz_r_95[6] = {  1638,      0, -1638, 
                                                 32767, -29605, 29572 };

/* 2.4 kHz bandpass. w = 18 degrees. r = 0.90 */
const signed int IIR_band_pass_2400Hz_r_90[6] = {  3277,      0,  -3277, 
                                                 32767, -28047,  26541 };

/* 2.4 kHz bandpass. w = 18 degrees. r = 0.85 */
const signed int IIR_band_pass_2400Hz_r_85[6] = {  4915,      0,  -4915, 
                                                 32767, -26489,  23674 };

/* 2.4 kHz bandpass. w = 18 degrees. r = 0.80 */
const signed int IIR_band_pass_2400Hz_r_80[6] = {  6553,     0,  -6654,
                                                 32767, -24930, 20971 };

/* 2.4 kHz bandpass. w = 18 degrees. r = 0.75 */
const signed int IIR_band_pass_2400Hz_r_75[6] = {  8192,      0, -8192, 
                                                 32767, -23372, 18431 };

#endif

/*****************************************************************************/
/* End of IIR_band_pass_filters.h                                            */
/*****************************************************************************/
