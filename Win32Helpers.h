#pragma once
#include <windows.h>
#include "Rect.h"

class Win32Helpers
{
public:
	BITMAPINFOHEADER CreateBitmapHeader32BitRGB(int width, int height);

	// From Microsoft's web site for more generic image dump.
	PBITMAPINFO CreateBitmapInfoStruct(HBITMAP hBmp);

	// From Microsoft's web site for more generic image dump.
	// 0 on success, else error number.
	int CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi, HBITMAP hBMP, HDC hDC);

};

