#include "CameraAttnSpotIO.h"

namespace SRS22 {
	CameraAttnSpotIO::CameraAttnSpotIO() :
		IOCommon(), rect(0, 0, 0, 0), _cameraRect(0, 0, 0, 0) {
		IOCOMMON_SETCLASSNAME;

	}

	CameraAttnSpotIO::CameraAttnSpotIO(Point p, int w, int h, Rect cameraRect) :
		IOCommon(), rect(p.X - w / 2, p.Y - w / 2, w, h), _cameraRect(cameraRect)
	{
		IOCOMMON_SETCLASSNAME;
	}

	CameraAttnSpotIO::~CameraAttnSpotIO() {

	}

	bool CameraAttnSpotIO::Init(Point p, int w, int h, Rect cameraRect) {
		IOCommon::Init();
		rect = Rect(p.X, p.Y, w, h);
		_cameraRect = cameraRect;
		return true;
	}

	void CameraAttnSpotIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void CameraAttnSpotIO::PreTick() {
		IOCommon::PreTick();
	}

	void CameraAttnSpotIO::PostTick() {
		IOCommon::PostTick();
	}

	void CameraAttnSpotIO::UnitTest() {

	}

	void CameraAttnSpotIO::ForceOnScreen() {
		rect.ForceInRect(_cameraRect);
	}

	void CameraAttnSpotIO::SetPt(Point& pt) {
		rect.CenterOn(pt);
		ForceOnScreen();
	}

}
