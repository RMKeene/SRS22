#pragma once

#include "fit_fft.h"

namespace SRS22 {
	void SRS22DebugBreak(int i, float f);
	void SRS22DebugBreak(int i);
	float SRSFastSqrt(float x);

	// Convert ulawbyte to 16 bit signed amplitude.
	int ulaw2linear(unsigned char ulawbyte);

}