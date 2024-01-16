#include "../../pch.h"
#include "ScreenAttnSpotIO.h"

namespace SRS22 {
	bool ScreenAttnSpotIO::freezeAttnSpotPosition = false;

	ScreenAttnSpotIO::ScreenAttnSpotIO() :
		AttnSpotBaseIO() {
		IOCOMMON_SETCLASSNAME;
	}

	ScreenAttnSpotIO::ScreenAttnSpotIO(Point p, int w, int h, Rect screenRect) :
		AttnSpotBaseIO()
	{
		IOCOMMON_SETCLASSNAME;
	}

	ScreenAttnSpotIO::~ScreenAttnSpotIO() {
	}

	bool ScreenAttnSpotIO::Init(Point p, int w, int h, Rect screenRect) {
		return AttnSpotBaseIO::Init(p, w, h, screenRect);
	}

	void ScreenAttnSpotIO::Shutdown() {
		AttnSpotBaseIO::Shutdown();
	}

	void ScreenAttnSpotIO::PreTickHardwareAndIO() {
		AttnSpotBaseIO::PreTickHardwareAndIO(freezeAttnSpotPosition);
	}

	void ScreenAttnSpotIO::PostTickHardwareAndUI() {
		AttnSpotBaseIO::PostTickHardwareAndUI();
	}

	void ScreenAttnSpotIO::ForceToBeSubclassed() {}

	void ScreenAttnSpotIO::UnitTest() {
	}
}