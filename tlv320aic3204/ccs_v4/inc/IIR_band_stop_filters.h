/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	IIR_band_stop_filters.h                                                  */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR band stop and IIR notch filters.                    */
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
/*   9th February 2010. Created by Richard Sikora.                           */
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

#ifndef IIR_BAND_STOP_FILTERS_H
#define IIR_BAND_STOP_FILTERS_H

/*****************************************************************************/
/* Bandstop filters designed using Bilinear Transform (BLT)                  */
/*****************************************************************************/

/* 9.5 kHz to 10.5 kHz band stop from Chassaing. */
const signed int IIR_band_stop_9500Hz_to_10500Hz[6] = { 30827, -9547, 30827, 
                                                       32767, -9547, 28891 };

/* Second order band stop 2000 Hz to 2800 Hz (nominally 2400 Hz) */
const signed int IIR_band_stop_2000Hz_to_2800Hz[6] = { 31135, -29652, 31135, 
                                                      32767, -29652, 29503 };

/* Second order band stop 600 Hz to 1.2 kHz */
const signed int IIR_band_stop_600Hz_to_1200Hz[6] =  { 31528, -31334, 31528, 
                                                      32767, -31334, 30289 };

/* Second order band stop 1.2 kHz to 2.4 kHz */
const signed int IIR_band_stop_1200Hz_to_2400Hz[6] = { 30359, -29617, 30359, 
                                                      32767, -29617, 27950 };

/* Second order band stop 2.4 kHz to 4.8 kHz */
const signed int IIR_band_stop_2400Hz_to_4800Hz[6] = { 28287, -25518, 28287, 
                                                      32767, -25518, 23807 };
                                                      
/* Second order band stop 4.8 kHz to 9.6 kHz */
const signed int IIR_band_stop_4800Hz_to_9600Hz[6] = { 24731, -15285, 24731,
                                                      32767, -15285, 16695 };
                                                      
/* Second order band stop 600 Hz to 2.4 kHz */
const signed int IIR_band_stop_600Hz_to_2400Hz[6] =  { 29229, -28937, 29229, 
                                                      32767, -28937, 25832 };

/* Second order band stop 1.2 kHz to 4.8 kHz */
const signed int IIR_band_stop_1200Hz_to_4800Hz[6] = { 26423, -25106, 26423, 
                                                      32767, -25106, 20080 };

/* Second order band stop 2.4 kHz to 9.6 kHz */
const signed int IIR_band_stop_2400Hz_to_9600Hz[6] = { 21707, -17227, 21707, 
                                                      32767, -17227, 10647 };
                                                      
/*****************************************************************************/
/* Notch filters designed by placing poles and zeroes.                       */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* Different frequency notch filters using r = 0.9372.                       */
/*                                                                           */
/*****************************************************************************/

/* 300 Hz notch. w = 2.25 degrees. r = 0.9372 */
const signed int IIR_notch_300Hz_r_9372[6] =  { 32767, -32742, 32767, 
                                                32767, -30686, 28781};

/* 600 Hz notch. w = 4.5 degrees. r = 0.9372 */
const signed int IIR_notch_600Hz_r_9372[6] =  { 32767, -32666, 32767, 
                                                32767, -30615, 28781};

/* 1.2 kHz notch. w = 9.0 degrees. r = 0.9372 */
const signed int IIR_notch_1200Hz_r_9372[6] = { 32767, -32364, 32767, 
                                                32767, -30331, 28781};

/* 2.4 kHz notch. w = 18 degrees. r = 0.9372 */
const signed int IIR_notch_2400Hz_r_9372[6] = { 32767, -31163, 32767, 
                                                32767, -29206, 28781};

/* 4.8 kHz notch. w = 36 degrees. r = 0.9372 */
const signed int IIR_notch_4800Hz_r_9372[6] = { 32767, -26509, 32767, 
                                                32767, -24844, 28781 };

/* 9.6 kHz notch. w = 72 degrees. r = 0.9372 */
const signed int IIR_notch_9600Hz_r_9372[6] = { 32767, -10126, 32767, 
                                                32767, -9490, 28781 };

/*****************************************************************************/
/* 2.4 kHz notch filters using different values of r.                        */
/*****************************************************************************/

/* 2.4 kHz notch. w = 18 degrees. r = 1.00 */
const signed int IIR_notch_2400Hz_r_100[6] = {  32767, -31163, 32767, 
                                                32767, -31163, 32767 };

/* 2.4 kHz notch. w = 18 degrees. r = 0.97 */
const signed int IIR_notch_2400Hz_r_97[6] = { 32767, -31163, 32767, 
                                              32767, -30228, 30830 };

/* 2.4 kHz notch. w = 18 degrees. r = 0.95 */
const signed int IIR_notch_2400Hz_r_95[6] = { 32767, -31163, 32767, 
                                              32767, -29605, 29572 };

/* 2.4 kHz notch. w = 18 degrees. r = 0.90 */
const signed int IIR_notch_2400Hz_r_90[6] = { 32767, -31163, 32767, 
                                              32767, -28047, 26541 };

/* 2.4 kHz notch. w = 18 degrees. r = 0.85 */
const signed int IIR_notch_2400Hz_r_85[6] = { 32767, -31163, 32767, 
                                              32767, -26489, 23674 };

/* 2.4 kHz notch. w = 18 degrees. r = 0.80 */
const signed int IIR_notch_2400Hz_r_80[6] = { 32767, -31163, 32767, 
                                              32767, -24930, 20971 };

/* 2.4 kHz notch. w = 18 degrees. r = 0.75 */
const signed int IIR_notch_2400Hz_r_75[6] = { 32767, -31163, 32767, 
                                              32767, -23372, 18431 };

#endif

/*****************************************************************************/
/* End of IIR_band_stop_filters.h                                            */
/*****************************************************************************/
