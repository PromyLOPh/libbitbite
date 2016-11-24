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
