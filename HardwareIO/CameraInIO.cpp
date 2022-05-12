#include "CameraInIO.h"

namespace SRS22 {
    CameraInIO::CameraInIO() : IOCommon() {

    }

    CameraInIO::~CameraInIO() {

    }

    bool CameraInIO::Init() {
        IOCommon::Init();
        return true;
    }

    void CameraInIO::Shutdown() {
        IOCommon::Shutdown();
    }

    void CameraInIO::PreTick() {
        AcquireFrame();
    }

    void CameraInIO::PostTick() {

    }

    void CameraInIO::UnitTest() {

    }

    bool CameraInIO::AcquireFrame() {
        return vidHelper.CaptureFrame();
    }


}
