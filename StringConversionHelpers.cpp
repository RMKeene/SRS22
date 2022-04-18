#include "pch.h"
#include "StringConversionHelpers.h"
#include <codecvt>

namespace SRS22 {

	int StringConversionHelpers::CharToWChar(const char* charIn, wchar_t* wcharOut, int wcharOutSz) {
		size_t n = mbstowcs(wcharOut, charIn, wcharOutSz - 1);
		wcharOut[wcharOutSz - 1] = 0;
		return n;
	}


}