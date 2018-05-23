/*
Copyright (c) 2015–2018 Lars-Dominik Braun <lars@6xq.net>

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#pragma once

#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
	/* data buffer start and current position */
	uint32_t *dataStart, *dataPos;
	/* total number of bits stored, and max number of bits stored (multiple of 8) */
	uint32_t totalBits, maxBits;
	/* current shift */
	uint8_t shiftPos;
} bitbuffer;

void bitbufferInit (bitbuffer * const bb, uint32_t * const buf, const uint32_t maxBits);
bool bitbufferPush32 (bitbuffer * const bb, const uint32_t data, const size_t bits);

inline static uint32_t *bitbufferGet (bitbuffer * const bb) {
	return bb->dataStart;
}

inline static uint32_t bitbufferLength (bitbuffer * const bb) {
	return bb->totalBits;
}
