#include "CameraInIO.h"

namespace SRS22 {
    CameraInIO::CameraInIO() : IOCommon() {
        IOCOMMON_SETCLASSNAME;

    }

    CameraInIO::~CameraInIO() {

    }

    bool CameraInIO::Init() {
        IOCommon::Init();
        return true;
    }

    void CameraInIO::Shutdown() {
        vidHelper.Shutdown();
        IOCommon::Shutdown();
    }

    void CameraInIO::PreTick() {
        IOCommon::PreTick();
        AcquireFrame();
    }

    void CameraInIO::PostTick() {
        IOCommon::PostTick();
    }

    void CameraInIO::UnitTest() {

    }

    bool CameraInIO::AcquireFrame() {
        return vidHelper.CaptureFrame();
    }


}
