#pragma once

namespace SRS22 {

	class ScreenInput
	{
	public:
		int GetScreenWidth();
		int GetScreenHeight();
		bool TakeScreenSnapshot(unsigned int* data, int& w, int& h);
	};

}
