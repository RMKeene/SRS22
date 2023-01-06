#include "pch.h"
#include "FastRand.h"

namespace SRS22 {
	static unsigned long x = 123456789, y = 362436069, z = 521288629;

	unsigned long xorshf96(void) { //period 2^96-1
		x ^= x << 16;
		x ^= x >> 5;
		x ^= x << 1;

		const unsigned long t = x;
		x = y;
		y = z;
		z = t ^ x ^ y;

		return z;
	}
}