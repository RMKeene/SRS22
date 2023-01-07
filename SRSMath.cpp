#include "SRSMath.h" 
#include "HardwareRaw/WaveInConstants.h"

namespace SRS22 {

	float SRSFastSqrt(float x)
	{
		const float xhalf = 0.5f * x;
		int i = *(int*)&x;
		i = 0x5f375a84 - (i >> 1);
		x = *(float*)&i;

		x = x * (1.5f - xhalf * x * x);
		return 1.0f / x;
	}

	int ulaw2linear(unsigned char ulawbyte)
	{
		static int exp_lut[8] = { 0,132,396,924,1980,4092,8316,16764 };
		int sign, exponent, mantissa, sample;

		ulawbyte = ~ulawbyte;
		sign = (ulawbyte & 0x80);
		exponent = (ulawbyte >> 4) & 0x07;
		mantissa = ulawbyte & 0x0F;
		sample = exp_lut[exponent] + (mantissa << (exponent + 3));
		if (sign != 0) sample = -sample;

		return(sample);
	}

	float SingleFreqDetect(const char* data, const int bufSize, const int FreqCyclesPerSec) {
		if (FreqCyclesPerSec > SRS22SAMPLEFREQ / 4)
			return 0.0f;

		const int halfLength = HALFINTERVAL(FreqCyclesPerSec);
		const int quarterLength = halfLength / 2;

		int aSum = 0;
		int bSum = 0;

		for (int i = 0; i < bufSize; i++) {
			const int c = ulaw2linear(data[i]);
			if (i % halfLength == 0)
				aSum += c;
			else
				aSum -= c;
			if ((i + quarterLength) % halfLength == 0)
				bSum += c;
			else
				bSum -= c;
		}
		const float sumSq = aSum * aSum + bSum * bSum;
		// Sqrt and scale to 0.0 to 1.0 range.
		return std::clamp(SRSFastSqrt(sumSq) / ((float)bufSize * 50.0f), 0.0f, 1.0f);
	}

}