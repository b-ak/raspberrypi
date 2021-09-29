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

#define DEBUG
#undef DEBUG

/* The Base64 index table */
static const char base64_lut[] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

uint32_t encode_base_64(uint8_t *encoded, const char *src, uint32_t len)
{
	uint32_t i;
	uint8_t *p;

#ifdef DEBUG
	printf("%s\n", __func__);
	printf("%s %s\n", encoded, src);
#endif

	if (!len)
		return 1;

	p = encoded;

	for (i = 0; i < len - 2; i += 3) {
		*p++ = base64_lut[(src[i] >> 2) & 0x3F];
		*p++ = base64_lut[((src[i] & 0x3) << 4) |
			((int) (src[i + 1] & 0xF0) >> 4)];
		*p++ = base64_lut[((src[i + 1] & 0xF) << 2) |
			((int) (src[i + 2] & 0xC0) >> 6)];
		*p++ = base64_lut[src[i + 2] & 0x3F];
	}

	if (i < len) {
		*p++ = base64_lut[(src[i] >> 2) & 0x3F];
		if (i == (len - 1)) {
			*p++ = base64_lut[((src[i] & 0x3) << 4)];
			*p++ = '=';
		}
		else {
			*p++ = base64_lut[((src[i] & 0x3) << 4) |
				((int) (src[i + 1] & 0xF0) >> 4)];
			*p++ = base64_lut[((src[i + 1] & 0xF) << 2)];
		}
		*p++ = '=';
	}

	return (p - encoded);
}


