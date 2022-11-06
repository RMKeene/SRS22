#include "pch.h"
#include "StringConversionHelpers.h"
#include <codecvt>

namespace SRS22 {
	int StringConversionHelpers::CharToWChar(const char* charIn, wchar_t* wcharOut, int wcharOutSz) {
		size_t n = mbstowcs(wcharOut, charIn, wcharOutSz - 1);
		wcharOut[wcharOutSz - 1] = 0;
		return n;
	}

	std::wstring StringConversionHelpers::str_2_wstr(std::string& str) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.from_bytes(str);
	}

	std::string StringConversionHelpers::wstr_2_str(std::wstring& wstr) {
		using convert_typeX = std::codecvt_utf8<wchar_t>;
		std::wstring_convert<convert_typeX, wchar_t> converterX;
		return converterX.to_bytes(wstr);
	}
}