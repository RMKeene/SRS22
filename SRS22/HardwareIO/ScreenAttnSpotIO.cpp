#include "ScreenAttnSpotIO.h"

namespace SRS22 {
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
		IOCommon::Shutdown();
	}

	void ScreenAttnSpotIO::PreTickHardwareAndIO() {
		IOCommon::PreTickHardwareAndIO();
	}

	void ScreenAttnSpotIO::PostTickHardwareAndUI() {
		IOCommon::PostTickHardwareAndUI();
	}

	void ScreenAttnSpotIO::ForceToBeSubclassed() {}

	void ScreenAttnSpotIO::UnitTest() {
	}
}