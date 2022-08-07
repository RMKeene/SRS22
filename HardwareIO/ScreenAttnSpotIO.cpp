#include "ScreenAttnSpotIO.h"

namespace SRS22 {
	ScreenAttnSpotIO::ScreenAttnSpotIO() :
		IOCommon(), rect(0, 0, 0, 0), _screenRect(0, 0, 0, 0) {
		IOCOMMON_SETCLASSNAME;

	}

	ScreenAttnSpotIO::ScreenAttnSpotIO(Point p, int w, int h, Rect screenRect) :
		IOCommon(), rect(p.X - w / 2, p.Y - w / 2, w, h), _screenRect(screenRect)
	{
		IOCOMMON_SETCLASSNAME;
	}

	ScreenAttnSpotIO::~ScreenAttnSpotIO() {

	}

	bool ScreenAttnSpotIO::Init(Point p, int w, int h, Rect screenRect) {
		IOCommon::Init();
		rect = Rect(p.X, p.Y, w, h);
		_screenRect = screenRect;
		return true;
	}

	void ScreenAttnSpotIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void ScreenAttnSpotIO::PreTick() {
		IOCommon::PreTick();
	}

	void ScreenAttnSpotIO::PostTick() {
		IOCommon::PostTick();
	}

	void ScreenAttnSpotIO::UnitTest() {

	}

	void ScreenAttnSpotIO::ForceOnScreen() {
		rect = rect.ForceInRect(_screenRect);
	}

	void ScreenAttnSpotIO::SetPt(Point& pt) {
		rect.CenterOnInPlace(pt);
		ForceOnScreen();
	}

}
