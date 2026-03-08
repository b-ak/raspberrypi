/*****************************************************************************/
/*                                                                           */
/* FILENAME                                                                  */
/* 	IIR_filters_fourth_order.h                                               */
/*                                                                           */
/* DESCRIPTION                                                               */
/*   Header file for fourth order IIR filters type I and type II.            */
/*                                                                           */
/* REVISION                                                                  */
/*   Revision: 1.00	                                                         */
/*   Author  : Richard Sikora                                                */
/*---------------------------------------------------------------------------*/
/*                                                                           */
/* HISTORY                                                                   */
/*   Revision 1.00                                                           */
/*   20th November 2002. Created by Richard Sikora.                          */
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

#ifndef IIR_FILTERS_FOURTH_ORDER_H
#define IIR_FILTERS_FOURTH_ORDER_H

signed int* fourth_order_IIR_direct_form_I_codec1( const signed int * coefficients, 
                                                 signed int input1, signed int input2);
signed int fourth_order_IIR_direct_form_I_codec2( const signed int * coefficients, 
                                                 signed int input);                                                                                            
signed int fourth_order_IIR_direct_form_IA( const signed int * coefficients, 
                                                 signed int input);
signed int fourth_order_IIR_direct_form_II( const signed int * coefficients, 
                                                  signed int input);
signed int fourth_order_IIR_direct_form_IH( const signed int * coefficients, 
                                                 signed int input);
 signed int fourth_order_IIR_direct_form_IHH( const signed int * coefficients, 
                                                 signed int input);                                                

#endif

/*****************************************************************************/
/* End of IIR_filters_fourth_order.h                                         */
/*****************************************************************************/
