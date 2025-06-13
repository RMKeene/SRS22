#include "SRSMath.h"
#include "HardwareRaw/WaveInConstants.h"
#include "Brain.h"

namespace SRS22 {

	void SRS22DebugBreak(int i, float f)
	{
		std::string conceptArray = Brain::FindArrayByCortexIdx(i);
		__debugbreak();
	}

	void SRS22DebugBreak(int i)
	{
		std::string conceptArray = Brain::FindArrayByCortexIdx(i);
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
	/// Finds the integer log. If x is 0 or 1, returns 0.
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

	int logBase2_U32(unsigned long x) {
		int result = 0;
		if (x >= 65536) { x >>= 16; result += 16; }
		if (x >= 256) { x >>= 8; result += 8; }
		if (x >= 16) { x >>= 4; result += 4; }
		if (x >= 4) { x >>= 2; result += 2; }
		if (x >= 2) { result += 1; }
		return result;
	}

	int logBase2_U64(unsigned long long x) {
		int result = 0;
		if (x >= 4294967296) { x >>= 32; result += 32; }
		if (x >= 65536) { x >>= 16; result += 16; }
		if (x >= 256) { x >>= 8; result += 8; }
		if (x >= 16) { x >>= 4; result += 4; }
		if (x >= 4) { x >>= 2; result += 2; }
		if (x >= 2) { result += 1; }
		return result;
	}

	float getDecayMultiplier(float timeInSeconds, float targetLevel, float initialValue)
	{
		const float maxValidTime = 7726194.0f; // Max time before float rounds multiplier to 1.0
		const float minValue = std::numeric_limits<float>::min(); // Avoid log(0)

		// Validate input
		if (timeInSeconds <= 0.0f || timeInSeconds > maxValidTime ||
			initialValue <= 0.0f ||
			targetLevel < minValue ||
			targetLevel >= initialValue)
		{
			throw std::invalid_argument("Invalid input for decay multiplier calculation.");
		}

		float ticks = timeInSeconds * 10.0f; // Convert to ticks (10 per second)
		return std::exp(std::log(targetLevel / initialValue) / ticks);
	}

	/**
	 * Calculates the per-tick multiplier to decay a value from 1.0 to a target level
	 * over a given time in seconds, using double-precision. Assumes 10 ticks per second.
	 *
	 * If the time is too large for meaningful precision (or the target level is invalid),
	 * the function returns 1.0 to indicate no significant decay.
	 *
	 * @param timeInSeconds   Duration over which decay should occur.
	 * @param targetLevel     Final value after decay from 1.0 (must be between 0 and 1). 0.1 default. Not 0 !
	 * @return                Multiplier to apply each tick (10 ticks per second).
	 */
	double getDecayMultiplier(double timeInSeconds, double targetLevel)
	{
		const double maxValidTime = 315576000.0; // 10 years

		// Validate input
		if (timeInSeconds <= 0.0 || targetLevel <= 0.0 || targetLevel >= 1.0 || timeInSeconds > maxValidTime)
		{
			return 1.0; // No decay or invalid input
		}

		double ticks = timeInSeconds * 10.0; // Convert to ticks (10 per second)
		return std::exp(std::log(targetLevel) / ticks);
	}
}