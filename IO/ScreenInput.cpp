#include "../pch.h"
#include <windows.h>
#include "ScreenInput.h"

namespace SRS22 {

	int ScreenInput::GetScreenWidth() {
		HDC hScreenDC = GetDC(nullptr);
		int width = GetDeviceCaps(hScreenDC, HORZRES);
		int height = GetDeviceCaps(hScreenDC, VERTRES);
		DeleteDC(hScreenDC);
		return width;
	}

	int ScreenInput::GetScreenHeight() {
		HDC hScreenDC = GetDC(nullptr);
		int width = GetDeviceCaps(hScreenDC, HORZRES);
		int height = GetDeviceCaps(hScreenDC, VERTRES);
		DeleteDC(hScreenDC);
		return height;
	}

	bool ScreenInput::TakeScreenSnapshot(unsigned int * data, int& w, int& h) {
		return true;
	}

}
