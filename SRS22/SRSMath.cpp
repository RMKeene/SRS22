#include "SRSMath.h"
#include "HardwareRaw/WaveInConstants.h"
#include "Brain.h"

namespace SRS22 {

	void SRS22DebugBreak(int i, float f)
	{
		std::string conceptMap = Brain::FindMapByCortexIdx(i);
		__debugbreak();
	}

	void SRS22DebugBreak(int i)
	{
		std::string conceptMap = Brain::FindMapByCortexIdx(i);
		__debugbreak();
	}

	void SRS22DebugBreak()
	{
		__debugbreak();
	}

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

	int logBase2_U8(unsigned char x) {
		int result = 0;
		if (x >= 16) { x >>= 4; result += 4; }
		if (x >= 4) { x >>= 2; result += 2; }
		if (x >= 2) { result += 1; }
		return result;
	}

	/// <summary>
	/// Finds the integer log. If x is 0 returns 0.
	/// </summary>
	/// <param name="x"></param>
	/// <returns></returns>
	int logBase2_U16(unsigned short x) {
		int result = 0;
		if (x >= 256) { x >>= 8; result += 8; }
		if (x >= 16) { x >>= 4; result += 4; }
		if (x >= 4) { x >>= 2; result += 2; }
		if (x >= 2) { result += 1; }
		return result;
	}

	int logBase2_U32(unsigned int x) {
		int result = 0;
		if (x >= 65536) { x >>= 16; result += 16; }
		if (x >= 256) { x >>= 8; result += 8; }
		if (x >= 16) { x >>= 4; result += 4; }
		if (x >= 4) { x >>= 2; result += 2; }
		if (x >= 2) { result += 1; }
		return result;
	} goofy here

	int logBase2_U64(unsigned long x) {
		int result = 0;
		if (x >= 4294967296) { x >>= 32; result += 32; }
		if (x >= 65536) { x >>= 16; result += 16; }
		if (x >= 256) { x >>= 8; result += 8; }
		if (x >= 16) { x >>= 4; result += 4; }
		if (x >= 4) { x >>= 2; result += 2; }
		if (x >= 2) { result += 1; }
		return result;
	}
}