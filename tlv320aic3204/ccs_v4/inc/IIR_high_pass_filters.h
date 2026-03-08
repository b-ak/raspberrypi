/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	 IIR_high_pass_filters.h                                                 */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for IIR low pass filters.                                   */
/*   Filters have been designed using the BLT from Butterworth filter.       */
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
/*   3rd December 2002. Created by Richard Sikora.                           */
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


#ifndef IIR_HIGH_PASS_FILTERS_H
#define IIR_HIGH_PASS_FILTERS_H

/*****************************************************************************/
/* First order IIR high pass filters.                                        */
/*****************************************************************************/

const signed int first_order_high_pass_1000Hz[6] = { 30766, -30766, 32767, -28736 };

const signed int first_order_high_pass_2000Hz[6] = { 28955, -28955, 32767, -25143 };

const signed int first_order_high_pass_4000Hz[6] = { 25843, -25843, 32767, -18918 };


/*****************************************************************************/
/* Second order IIR high pass filters.                                       */
/*****************************************************************************/

///* Second order high pass filter 300 Hz */
//const signed int IIR_high_pass_300Hz[6]  = { 31870, -31870, 31870, 
 //                                            32767, -31857, 30997   };

/* Second order high pass filter 300 Hz */
const signed int IIR_high_pass_300Hz[6]  = { 26527, -26515, 26527, 
                                             32767, -25915, 21486   };                                             

/* Second order high pass filter 600 Hz */
const signed int IIR_high_pass_600Hz[6]  = { 30997, -30997, 30997, 
                                             32767, -30949, 29322  };

/* Second order high pass filter 1000 Hz */
const signed int IIR_high_pass_1000Hz[6] = { 29870, -29870, 29870, 
                                             32767, -29742, 27330  };

/* Second order high pass filter 1200 Hz */
const signed int IIR_high_pass_1200Hz[6] = { 29322, -29322, 29322, 
                                             32767, -29135, 26240  };
                                             
/* Second order high pass filter 2000 Hz */
const signed int IIR_high_pass_2000Hz[6] = { 27226, -27226, 27226, 
                                             32767, -26754, 22629  };

/* Second order high pass filter 2400 Hz */
const signed int IIR_high_pass_2400Hz[6] = {  26233, -26233, 26233,
                                             32767,  -25575, 21015  };

/* Second order high pass filter 4000 Hz */
const signed int IIR_high_pass_4000Hz[6] = { 22587, -22587, 22587, 
                                             32767, -20964, 15649  };

/* Second order high pass filter 4800 Hz */
const signed int IIR_high_pass_4800Hz[6] = {  20936, -20936, 20936, 
                                             32767,  -18726, 13526  };

/* Second order high pass filter 9600 Hz */
const signed int IIR_high_pass_9600Hz[6] = {  12891, -12891, 12891, 
                                             32767,   -6053,  6416  };
                                             
#endif

/*****************************************************************************/
/* End of IIR_high_pass_filters.h                                            */
/*****************************************************************************/
