#pragma once

#include "fit_fft.h"

namespace SRS22 {

	float SRSFastSqrt(float x);

	// Convert ulawbyte to 16 bit signed amplitude.
	int ulaw2linear(unsigned char ulawbyte);
}