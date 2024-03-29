#include "AttnSpotBaseIO.h"

namespace SRS22 {
	AttnSpotBaseIO::AttnSpotBaseIO() :
		IOCommon(), rect(0, 0, 0, 0), _viewRect(0, 0, 0, 0) {
		IOCOMMON_SETCLASSNAME;
	}

	AttnSpotBaseIO::AttnSpotBaseIO(Point p, int w, int h, Rect viewRect) :
		IOCommon(), rect(p.X - w / 2, p.Y - w / 2, w, h), _viewRect(viewRect)
	{
		IOCOMMON_SETCLASSNAME;
	}

	AttnSpotBaseIO::~AttnSpotBaseIO() {
	}

	bool AttnSpotBaseIO::Init(Point p, int w, int h, Rect viewRect) {
		IOCommon::Init();
		rect = Rect(p.X, p.Y, w, h);
		_viewRect = viewRect;
		return true;
	}

	void AttnSpotBaseIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void AttnSpotBaseIO::PreTickHardwareAndIO(bool freezeLocation) {
		rectIsFrozen = freezeLocation;
		Rect rr = rect;
		frozenRect = rect;
		IOCommon::PreTickHardwareAndIO();
		previousRect = rr;
		if (freezeLocation) {
			rect = frozenRect;
		}
	}

	void AttnSpotBaseIO::PostTickHardwareAndUI() {
		IOCommon::PostTickHardwareAndUI();
	}

	void AttnSpotBaseIO::UnitTest() {
	}

	void AttnSpotBaseIO::ForceOnScreen() {
		rect = rect.ForceInRect(_viewRect);
	}

	void AttnSpotBaseIO::SetPt(Point& pt) {
		if (!rectIsFrozen) {
			rect.CenterOnInPlace(pt);
			ForceOnScreen();
		}
	}

	void AttnSpotBaseIO::SetPt(const int x, const int y) {
		if (!rectIsFrozen) {
			rect.CenterOnInPlace(x, y);
			ForceOnScreen();
		}
	}
}