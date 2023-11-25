#include "CameraAttnSpotIO.h"

namespace SRS22 {
	bool CameraAttnSpotIO::freezeAttnSpotPosition = false;

	CameraAttnSpotIO::CameraAttnSpotIO() :
		AttnSpotBaseIO() {
		IOCOMMON_SETCLASSNAME;
	}

	CameraAttnSpotIO::CameraAttnSpotIO(Point p, int w, int h, Rect cameraRect) :
		AttnSpotBaseIO(p, w, h, cameraRect)
	{
		IOCOMMON_SETCLASSNAME;
	}

	CameraAttnSpotIO::~CameraAttnSpotIO() {
	}

	bool CameraAttnSpotIO::Init(Point p, int w, int h, Rect cameraRect) {
		return AttnSpotBaseIO::Init(p, w, h, cameraRect);
	}

	void CameraAttnSpotIO::Shutdown() {
		AttnSpotBaseIO::Shutdown();
	}

	void CameraAttnSpotIO::PreTickHardwareAndIO() {
		AttnSpotBaseIO::PreTickHardwareAndIO(freezeAttnSpotPosition);
	}

	void CameraAttnSpotIO::PostTickHardwareAndUI() {
		AttnSpotBaseIO::PostTickHardwareAndUI();
	}

	void CameraAttnSpotIO::ForceToBeSubclassed() {}

	void CameraAttnSpotIO::UnitTest() {
	}
}