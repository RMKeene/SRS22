#include "../pch.h"
#include "ScreenInputIO.h"
#include "../Point.h"
#include "../OpenCVHelpers.h"

namespace SRS22 {

	ScreenInputIO::ScreenInputIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;

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
		IOCommon::Init();
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
		IOCommon::Shutdown();
	}

	void ScreenInputIO::PreTick() {
		IOCommon::PreTick();
		if (!currentScreen.empty())
			currentScreen.copyTo(previousScreen);
		if (!currentScreenLowRes.empty())
			currentScreenLowRes.copyTo(previousScreenLowRes);

		TakeScreenSnapshot();

		if (!currentScreen.empty()) {
			resize(currentScreen, currentScreenLowRes, cv::Size2i(AbsDiffWidth, AbsDiffHeight));
			// Debug
			// imshow("Screen Low Res", currentScreenLowRes);
		}
		if (!currentScreenLowRes.empty() &&
			!previousScreenLowRes.empty()) {
			// 8UC4 : dims=2 rows=270 cols=640"
			cv::absdiff(currentScreenLowRes, previousScreenLowRes, currentAbsDifferenceLowRes);
		}
	}

	void ScreenInputIO::PostTick() {
		IOCommon::PostTick();
	}

	int ScreenInputIO::GetScreenWidthWin32() {
		HDC hScreenDC = GetDC(nullptr);
		int width = GetDeviceCaps(hScreenDC, HORZRES);
		DeleteDC(hScreenDC);
		return width;
	}

	int ScreenInputIO::GetScreenHeightWin32() {
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

		if (!snapshotData) { // Reuse memory. 
			snapshotData = CreateCompatibleBitmap(hwindowDC, w, h);
			snapshotDataHeader = CreateBitmapHeader(w, h);
		}

		SelectObject(hwindowCompatibleDC, snapshotData);

		DWORD dwBmpSize = ((w * snapshotDataHeader.biBitCount + 31) / 32) * 4 * h;
		if (snapshotDataHeaderDIB == NULL)
			snapshotDataHeaderDIB = GlobalAlloc(GHND, dwBmpSize);
		if (snapshotDataHeaderDIB != 0) {
			char* lpbitmap = (char*)GlobalLock(snapshotDataHeaderDIB);

			// Copy from actual screen
			StretchBlt(hwindowCompatibleDC, 0, 0, w, h, hwindowDC, screenx, screeny, w, h, SRCCOPY);
			if (currentScreen.cols != w || currentScreen.rows != h) {
				currentScreen.create(h, w, CV_8UC4);
			}
			// Copy to the OpenCV Mat memory.
			GetDIBits(hwindowCompatibleDC, snapshotData, 0, height, currentScreen.data, (BITMAPINFO*)&snapshotDataHeader, DIB_RGB_COLORS);
		}

		DeleteDC(hwindowCompatibleDC);
		ReleaseDC(nullptr, hwindowDC);

		// For debug.
		//imshow("SCreen", currentScreen);

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

	bool ScreenInputIO::IsCorrectSize(cv::Mat& m) {
		return !m.empty() && m.rows == h && m.cols == w;
	}

	cv::Mat ScreenInputIO::GetCorrectSizeMat() {
		cv::Mat m;
		m.create(h, w, CV_8UC4);
		return m;
	}

	void ScreenInputIO::GetCurrentScreen(cv::Mat& outMat) {
		currentScreen.copyTo(outMat);
	}

	cv::Mat& ScreenInputIO::GetCurrentScreenRaw() {
		return currentScreen;
	}

	void ScreenInputIO::GetSubRect(cv::Mat& outM, const SRS22::Rect& region) {
		OpenCVHelpers::CVGetSubRectRGB(currentScreen, outM, region);
	}
}
