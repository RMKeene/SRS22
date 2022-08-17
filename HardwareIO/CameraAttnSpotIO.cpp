#include "CameraAttnSpotIO.h"

namespace SRS22 {
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

	void CameraAttnSpotIO::PreTick() {
		AttnSpotBaseIO::PreTick();
	}

	void CameraAttnSpotIO::PostTick() {
		AttnSpotBaseIO::PostTick();
	}

	void CameraAttnSpotIO::ForceToBeSubclassed() {}

	void CameraAttnSpotIO::UnitTest() {

	}

}
