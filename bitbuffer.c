#include "bitbuffer.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

bool bitbufferPush32 (bitbuffer * const bb, const uint32_t data, const size_t bits) {
	assert (bb != NULL);
	assert (bits > 0);

	uint32_t *dataPos = bb->dataPos;
	const uint32_t * const dataStart = bb->dataStart;
	const uint32_t dataLen = bb->maxBits/8;
	const uint32_t dataMasked = bits == sizeof (data)*8 ? data : data & ((1 << bits)-1);
	uint32_t shift = *dataPos;
	uint8_t shiftPos = bb->shiftPos;

	shift |= dataMasked << shiftPos;
	shiftPos += bits;
	if (shiftPos == sizeof (shift)*8) {
		*dataPos++ = shift;
		shiftPos = 0;
		shift = 0;
	} else if (shiftPos > sizeof (shift)*8) {
		*dataPos++ = shift;
		shiftPos = shiftPos % (sizeof (shift)*8);
		assert (bits >= shiftPos);
		shift = dataMasked >> (bits - shiftPos);
	}
	*dataPos = shift;

	bb->totalBits += bits;
	bb->shiftPos = shiftPos;
	bb->dataPos = dataPos;
}

void bitbufferInit (bitbuffer * const bb, uint32_t * const buf, const uint32_t maxBits) {
	assert (maxBits % 8 == 0);

	bb->maxBits = maxBits;
	bb->dataPos = buf;
	bb->dataStart = buf;
	bb->shiftPos = 0;
	bb->totalBits = 0;
}

