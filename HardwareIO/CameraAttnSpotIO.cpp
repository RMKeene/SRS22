#include "CameraAttnSpotIO.h"

namespace SRS22 {
    CameraAttnSpotIO::CameraAttnSpotIO() : IOCommon() {
        IOCOMMON_SETCLASSNAME;

    }

    CameraAttnSpotIO::CameraAttnSpotIO(Point p, Rect cameraRect) : IOCommon(), _p(p), _rect(cameraRect)
    {
        _rect.Clamp(_p);
    }


    CameraAttnSpotIO::~CameraAttnSpotIO() {

    }

    bool CameraAttnSpotIO::Init() {
        IOCommon::Init();
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



}
