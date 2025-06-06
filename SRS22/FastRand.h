#pragma once

namespace SRS22 {
	unsigned long xorshf96(void);
	void setSeed(unsigned long seed);

	/// <summary>
	/// Fast random long.
	/// </summary>
	/// <returns></returns>
	inline unsigned long fastRand() {
		return xorshf96();
	}

	/// <summary>
	/// Fast random long from 0 to 0x0FFFFFFFF inclusive.
	/// </summary>
	/// <returns></returns>
	inline long fastRange0Plus() {
		return fastRand() & 0x0FFFFFFFF;
	}

	/// <summary>
	/// Return a double from 0.0f to 1.0f exclusive.
	/// Granularity is 1.0 / 4294967296.0
	/// </summary>
	/// <returns></returns>
	inline double fastRandDouble() {
		return (fastRange0Plus() & 0x0FFFFFFFF) / 4294967296.0;
	}

	/// <summary>
	/// Return a float from 0.0f to 1.0f exclusive.
	/// 
	/// </summary>
	/// <returns></returns>
	inline float fastRandFloat() {
		return (float)fastRandDouble();
	}

	/// <summary>
	/// Return a double from -1.0f to 1.0f exclusive.
	/// 
	/// </summary>
	/// <returns></returns>
	inline double fastRandDoublePM() {
		// 0x0FFFFFFFF / 2147483648.0 is range 0.0 to 2.0 exclusive.
		return ((fastRange0Plus() & 0x0FFFFFFFF) / 2147483648.0) - 1.0;
	}

	/// <summary>
	/// Return a float from -1.0f to 1.0f exclusive.
	/// 
	/// </summary>
	/// <returns></returns>
	inline float fastRandFloatPM() {
		return (float)fastRandDoublePM();
	}
}
