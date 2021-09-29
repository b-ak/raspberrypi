/**
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
 **/

#include <stddef.h>
#include <stdint.h>

/*
 * @func: Get a Two byte input in ASCII convert it to Binary coded Hexadecimal
 *
 * @ascii_text - Two byte ASCII value
 * @bcd_value - Length equivalent of the ASCII input
 *
 */

uint8_t ascii_to_length(uint8_t *ascii_text)
{ 
	static uint8_t bcd_value;

    // MSB
    if(ascii_text[0] >= '0' && ascii_text[0] <= '9')
        bcd_value = (ascii_text[0] - '0')  << 4;
    else if (ascii_text[0] >= 'A' && ascii_text[0] <= 'F')
        bcd_value = (0xa + ascii_text[0] - 'A')  << 4;
    else if (ascii_text[0] >= 'a' && ascii_text[0] <= 'f')
        bcd_value = (0xa + ascii_text[0] - 'a')  << 4;
	else
		bcd_value = 0;

    // LSB
    if(ascii_text[1] >= '0' && ascii_text[1] <= '9')
        bcd_value |= (ascii_text[1] - '0');
    else if (ascii_text[1] >= 'A' && ascii_text[1] <= 'F')
        bcd_value |= (0xa + ascii_text[1] - 'A');
    else if (ascii_text[1] >= 'a' && ascii_text[1] <= 'f')
        bcd_value |= (0xa + ascii_text[1] - 'a');
	else
		bcd_value = 0;

	return bcd_value;
}
