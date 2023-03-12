#include "pch.h"
#include "tinyfloat.h"

namespace SRS22 {
	const int tinyfloat::TINYFLOATOFFSET = 128;
	const float tinyfloat::TINYFLOATOFFSETF = 128.0f;
	const float tinyfloat::TINYFLOATSCALE = 64.0f;
	const int tinyfloat::TINYFLOATSMIN = 0;
	const int tinyfloat::TINYFLOATSMAX = 255;
	// Actually 0.0000001 greater than the max error.
	const float tinyfloat::TINYFLOATTOLLERANCE = 0.015626f;

}