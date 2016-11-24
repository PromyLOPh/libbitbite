/*	Generic bit buffer, assembling a byte string from individual pushed bits
 */

#include "bitbuffer.h"
#include <stdbool.h>
#include <stdio.h>
#include <assert.h>

/*	Return only the first bits of data
 */
static uint32_t maskBits (uint32_t data, const uint8_t bits) {
	return bits == sizeof (data)*8 ? data : data & ((1 << bits)-1);
}

/*	Push at most bits into bitbuffer
 */
bool bitbufferPush32 (bitbuffer * const bb, const uint32_t data, const size_t bits) {
	assert (bb != NULL);
	assert (bits > 0);

	if (bb->totalBits + bits > bb->maxBits) {
		return false;
	}

	uint32_t *dataPos = bb->dataPos;
	const uint32_t * const dataStart = bb->dataStart;
	const uint32_t dataLen = bb->maxBits/8;
	const uint32_t dataMasked = maskBits (data, bits);
	uint8_t shiftPos = bb->shiftPos;
	uint32_t shift = maskBits (*dataPos, shiftPos);

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

	return true;
}

/*	Initialize bitbuffer, assigning buf as backing store of at least maxBits
 *	length
 */
void bitbufferInit (bitbuffer * const bb, uint32_t * const buf, const uint32_t maxBits) {
	assert (maxBits % 8 == 0);

	bb->maxBits = maxBits;
	bb->dataPos = buf;
	bb->dataStart = buf;
	bb->shiftPos = 0;
	bb->totalBits = 0;
}

