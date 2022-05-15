#include "../pch.h"
#include "ScreenInputIO.h"

namespace SRS22 {

	ScreenInputIO::ScreenInputIO() {
		HDC hScreenDC = GetDC(nullptr);
		w = GetDeviceCaps(hScreenDC, HORZRES);
		h = GetDeviceCaps(hScreenDC, VERTRES);
		// Shut the compiler warning about uninitialized variable off.
		snapshotDataHeader.biWidth = 0; 
		DeleteDC(hScreenDC);
	}

	ScreenInputIO::~ScreenInputIO() {
		if (snapshotData) {
			DeleteObject(snapshotData);
			DeleteObject(snapshotDataHeaderDIB);
		}
	}

	bool ScreenInputIO::Init() {
		HDC hScreenDC = GetDC(nullptr);
		w = GetDeviceCaps(hScreenDC, HORZRES);
		h = GetDeviceCaps(hScreenDC, VERTRES);
		DeleteDC(hScreenDC);
		return true;
	}

	void ScreenInputIO::Shutdown() {
		if (snapshotData) {
			DeleteObject(snapshotData);
		}
	}

	void ScreenInputIO::PreTick() {
		IOCommon::PreTick();
	}

	void ScreenInputIO::PostTick() {
		IOCommon::PostTick();
	}

	int ScreenInputIO::GetScreenWidth() {
		HDC hScreenDC = GetDC(nullptr);
		int width = GetDeviceCaps(hScreenDC, HORZRES);
		DeleteDC(hScreenDC);
		return width;
	}

	int ScreenInputIO::GetScreenHeight() {
		HDC hScreenDC = GetDC(nullptr);
		int height = GetDeviceCaps(hScreenDC, VERTRES);
		DeleteDC(hScreenDC);
		return height;
	}

	BITMAPINFOHEADER ScreenInputIO::CreateBitmapHeader(int width, int height)
	{
		BITMAPINFOHEADER  bi;

		// create a bitmap
		bi.biSize = sizeof(BITMAPINFOHEADER);
		bi.biWidth = width;
		bi.biHeight = -height;  //this is the line that makes it draw upside down or not
		bi.biPlanes = 1;
		bi.biBitCount = 32;
		bi.biCompression = BI_RGB;
		bi.biSizeImage = 0;
		bi.biXPelsPerMeter = 0;
		bi.biYPelsPerMeter = 0;
		bi.biClrUsed = 0;
		bi.biClrImportant = 0;

		return bi;
	}

	bool ScreenInputIO::TakeScreenSnapshot() {
		// get full screen device context.
		HDC hwindowDC = GetDC(nullptr);
		HDC hwindowCompatibleDC = CreateCompatibleDC(hwindowDC);
		SetStretchBltMode(hwindowCompatibleDC, COLORONCOLOR);

		int screenx = GetSystemMetrics(SM_XVIRTUALSCREEN);
		int screeny = GetSystemMetrics(SM_YVIRTUALSCREEN);
		int width = GetSystemMetrics(SM_CXSCREEN);
		int height = GetSystemMetrics(SM_CYSCREEN);

		if (!snapshotData) {
			snapshotData = CreateCompatibleBitmap(hwindowDC, width, height);
			snapshotDataHeader = CreateBitmapHeader(width, height);
		}

		SelectObject(hwindowCompatibleDC, snapshotData);

		DWORD dwBmpSize = ((width * snapshotDataHeader.biBitCount + 31) / 32) * 4 * height;
		if(snapshotDataHeaderDIB == NULL)
			snapshotDataHeaderDIB = GlobalAlloc(GHND, dwBmpSize);
		if (snapshotDataHeaderDIB != 0) {
			char* lpbitmap = (char*)GlobalLock(snapshotDataHeaderDIB);

			StretchBlt(hwindowCompatibleDC, 0, 0, width, height, hwindowDC, screenx, screeny, width, height, SRCCOPY);   //change SRCCOPY to NOTSRCCOPY for wacky colors !
			GetDIBits(hwindowCompatibleDC, snapshotData, 0, height, lpbitmap, (BITMAPINFO*)&snapshotDataHeader, DIB_RGB_COLORS);
		}

		DeleteDC(hwindowCompatibleDC);
		ReleaseDC(nullptr, hwindowDC);

		return true;
	}

	PBITMAPINFO ScreenInputIO::CreateBitmapInfoStruct(HBITMAP hBmp)
	{
		BITMAP bmp;
		PBITMAPINFO pbmi;
		WORD    cClrBits;

		// Retrieve the bitmap color format, width, and height.  
		if (!GetObject(hBmp, sizeof(BITMAP), (LPSTR)&bmp))
			throw "Cant create bitmap info?";

		// Convert the color format to a count of bits.  
		cClrBits = (WORD)(bmp.bmPlanes * bmp.bmBitsPixel);
		if (cClrBits == 1)
			cClrBits = 1;
		else if (cClrBits <= 4)
			cClrBits = 4;
		else if (cClrBits <= 8)
			cClrBits = 8;
		else if (cClrBits <= 16)
			cClrBits = 16;
		else if (cClrBits <= 24)
			cClrBits = 24;
		else cClrBits = 32;

		// Allocate memory for the BITMAPINFO structure. (This structure  
		// contains a BITMAPINFOHEADER structure and an array of RGBQUAD  
		// data structures.)  
		if (cClrBits < 24)
#pragma warning( push )
#pragma warning( disable : 26451 )
#pragma warning( disable : 6297 )
#pragma warning( disable : 4334 )
			pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
				sizeof(BITMAPINFOHEADER) +
				sizeof(RGBQUAD) * (1 << cClrBits));
#pragma warning( pop )
		// There is no RGBQUAD array for these formats: 24-bit-per-pixel or 32-bit-per-pixel 

		else
			pbmi = (PBITMAPINFO)LocalAlloc(LPTR,
				sizeof(BITMAPINFOHEADER));

		if (pbmi == NULL)
			throw "Cant create bitmap info? Out of memory?";
		// Initialize the fields in the BITMAPINFO structure.  

		pbmi->bmiHeader.biSize = (DWORD)sizeof(BITMAPINFOHEADER);
		pbmi->bmiHeader.biWidth = bmp.bmWidth;
		pbmi->bmiHeader.biHeight = bmp.bmHeight;
		pbmi->bmiHeader.biPlanes = bmp.bmPlanes;
		pbmi->bmiHeader.biBitCount = bmp.bmBitsPixel;
		if (cClrBits < 24)
			pbmi->bmiHeader.biClrUsed = (1 << cClrBits);

		// If the bitmap is not compressed, set the BI_RGB flag.  
		pbmi->bmiHeader.biCompression = BI_RGB;

		// Compute the number of bytes in the array of color  
		// indices and store the result in biSizeImage.  
		// The width must be DWORD aligned unless the bitmap is RLE 
		// compressed. 
		pbmi->bmiHeader.biSizeImage = ((pbmi->bmiHeader.biWidth * cClrBits + 31) & ~31) / 8
			* pbmi->bmiHeader.biHeight;
		// Set biClrImportant to 0, indicating that all of the  
		// device colors are important.  
		pbmi->bmiHeader.biClrImportant = 0;
		return pbmi;
	}

	int ScreenInputIO::CreateBMPFile(LPTSTR pszFile, PBITMAPINFO pbi,
		HBITMAP hBMP, HDC hDC)
	{
		HANDLE hf;                 // file handle  
		BITMAPFILEHEADER hdr;       // bitmap file-header  
		PBITMAPINFOHEADER pbih;     // bitmap info-header  
		LPBYTE lpBits;              // memory pointer  
		DWORD dwTotal;              // total count of bytes  
		DWORD cb;                   // incremental count of bytes  
		BYTE* hp;                   // byte pointer  
		DWORD dwTmp;

		pbih = (PBITMAPINFOHEADER)pbi;
		lpBits = (LPBYTE)GlobalAlloc(GMEM_FIXED, pbih->biSizeImage);

		if (!lpBits)
			return 1;

		// Retrieve the color table (RGBQUAD array) and the bits  
		// (array of palette indices) from the DIB.  
		if (!GetDIBits(hDC, hBMP, 0, (WORD)pbih->biHeight, lpBits, pbi,
			DIB_RGB_COLORS))
		{
			return 2;
		}

		// Create the .BMP file.  
		hf = CreateFile(pszFile,
			GENERIC_READ | GENERIC_WRITE,
			(DWORD)0,
			NULL,
			CREATE_ALWAYS,
			FILE_ATTRIBUTE_NORMAL,
			(HANDLE)NULL);
		if (hf == INVALID_HANDLE_VALUE)
			return 3;
		hdr.bfType = 0x4d42;        // 0x42 = "B" 0x4d = "M"  
		// Compute the size of the entire file.  
		hdr.bfSize = (DWORD)(sizeof(BITMAPFILEHEADER) +
			pbih->biSize + pbih->biClrUsed
			* sizeof(RGBQUAD) + pbih->biSizeImage);
		hdr.bfReserved1 = 0;
		hdr.bfReserved2 = 0;

		// Compute the offset to the array of color indices.  
		hdr.bfOffBits = (DWORD)sizeof(BITMAPFILEHEADER) +
			pbih->biSize + pbih->biClrUsed
			* sizeof(RGBQUAD);

		// Copy the BITMAPFILEHEADER into the .BMP file.  
		if (!WriteFile(hf, (LPVOID)&hdr, sizeof(BITMAPFILEHEADER),
			(LPDWORD)&dwTmp, NULL))
		{
			return 4;
		}

		// Copy the BITMAPINFOHEADER and RGBQUAD array into the file.  
		if (!WriteFile(hf, (LPVOID)pbih, sizeof(BITMAPINFOHEADER)
			+ pbih->biClrUsed * sizeof(RGBQUAD),
			(LPDWORD)&dwTmp, (NULL)))
			return 5;

		// Copy the array of color indices into the .BMP file.  
		dwTotal = cb = pbih->biSizeImage;
		hp = lpBits;
		if (!WriteFile(hf, (LPSTR)hp, (int)cb, (LPDWORD)&dwTmp, NULL))
			return 6;

		// Close the .BMP file.  
		if (!CloseHandle(hf))
			return 7;

		// Free memory.  
		GlobalFree((HGLOBAL)lpBits);

		// Ok
		return 0;
	}

	void ScreenInputIO::DumpCurrentScreenSnapshot(LPCTSTR fname) {
		HDC hDC = GetDC(nullptr);
		PBITMAPINFO bi = CreateBitmapInfoStruct(snapshotData);
		CreateBMPFile((LPTSTR)fname, bi, snapshotData, hDC);
		DeleteObject(bi);
		DeleteDC(hDC);
	}
}
