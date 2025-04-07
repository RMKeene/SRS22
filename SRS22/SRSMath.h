#pragma once

#include "fit_fft.h"

namespace SRS22 {
	void SRS22DebugBreak(int i, float f);
	void SRS22DebugBreak(int i);
	float SRSFastSqrt(float x);

	// Convert ulawbyte to 16 bit signed amplitude.
	int ulaw2linear(unsigned char ulawbyte);

	int logBase2_U8(unsigned char x);
	int logBase2_U16(unsigned short x);
	int logBase2_U32(unsigned long x);
	int logBase2_U64(unsigned long long x);

	 /**
	  * Calculates the per-tick decay multiplier to reduce a value from initialValue (1) to targetLevel (0.1)
	  * over the given duration in seconds, assuming 10 ticks per second.
	  * Suggested to use this only for constant initialization of decay multipliers.
	  * Do not use on every neuron or link every tick!
	  *
	  * @param timeInSeconds  Duration of decay in seconds (must be > 0 and <= 7,726,194).
	  * @param targetLevel    Final value after decay (must be > 0 and < initialValue).
	  * @param initialValue   Starting value before decay (must be > 0).
	  * @return               The multiplier to apply each tick to achieve the target level.
	  * @throws std::invalid_argument if inputs are out of valid range.
	  */
	float getDecayMultiplier(float timeInSeconds, float targetLevel = 0.1f, float initialValue = 1.0f)
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
	double getDecayMultiplier(double timeInSeconds, double targetLevel = 0.1)
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

	/*
		Derivation of the multiplier formula:
		We want the value to decay from 1.0 to targetLevel over a number of ticks.
			multiplier^ticks = targetLevel
		Solving for multiplier:
		1. Take the natural log of both sides:
			ticks * log(multiplier) = log(targetLevel)
		2. Divide both sides by ticks:
			log(multiplier) = log(targetLevel) / ticks
		3. Apply the exponential function to both sides:
			multiplier = exp(log(targetLevel) / ticks)
		This gives the per-tick multiplier needed to decay a value from 1.0 to
		targetLevel over the specified number of ticks.
	*/
}
