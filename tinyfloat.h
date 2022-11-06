#pragma once

namespace SRS22 {
	typedef unsigned char tinyfloatprim;

	/// <summary>
	/// Our compact floating point value. Approx +-2.0f represented in 8 bits fixed point.
	/// Actual range is -2.000 to 1.984375 inclusive. Steps of 0.015625
	/// </summary>
	struct tinyfloat
	{
		unsigned char v;

		explicit tinyfloat(tinyfloatprim val) {
			v = val;
		}

		explicit tinyfloat(float val) {
			v = f2tfprim(val);
		}

		static const int TINYFLOATOFFSET;
		static const float TINYFLOATOFFSETF;
		static const float TINYFLOATSCALE;
		static const int TINYFLOATSMIN;
		static const int TINYFLOATSMAX;

		static inline float tf2f(const tinyfloat& tf) {
			return ((float)tf.v - TINYFLOATOFFSETF) / TINYFLOATSCALE;
		}

		static inline tinyfloatprim f2tfprim(const float f) {
			const int vv = (int)(f * TINYFLOATSCALE + TINYFLOATOFFSETF);
			if (vv < TINYFLOATSMIN) return TINYFLOATSMIN;
			else if (vv > TINYFLOATSMAX) return TINYFLOATSMAX;
			return (tinyfloatprim)vv;
		}

		static inline tinyfloat f2tf(const float f) {
			return tinyfloat(f2tfprim(f));
		}

		tinyfloat operator=(tinyfloat f) {}
	};
}
