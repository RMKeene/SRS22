#pragma once

namespace SRS22 {
	class StringConversionHelpers
	{
	public:

		/// <summary>
		/// Returns how many wchars long wcharOut is. Will convert at most wcharOutSz - 1 characters, and always 0 terminates wcharOut.
		/// </summary>
		/// <param name="charIn"></param>
		/// <param name="wcharOut"></param>
		/// <param name="wcharOutSz"></param>
		/// <returns></returns>
		static int CharToWChar(const char* charIn, wchar_t* wcharOut, int wcharOutSz);

		static std::wstring str_2_wstr(std::string& str);
		static std::string wstr_2_str(std::wstring& str);
	};
}
