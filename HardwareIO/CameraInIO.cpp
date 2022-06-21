#include "CameraInIO.h"
#include "../OpenCVHelpers.h"

namespace SRS22 {
    CameraInIO::CameraInIO() : IOCommon() {
        IOCOMMON_SETCLASSNAME;

    }

    CameraInIO::~CameraInIO() {

    }

    bool CameraInIO::Init() {
        IOCommon::Init();
        w = GetCameraWidthWin32();
        h = GetCameraHeightWin32();
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

    int CameraInIO::GetCameraWidthWin32() {
        return vidHelper.GetCameraWidthWin32();
    }

    int CameraInIO::GetCameraHeightWin32() {
        return vidHelper.GetCameraHeightWin32();
    }

    bool CameraInIO::AcquireFrame() {
        return vidHelper.CaptureFrame();
    }

    void CameraInIO::GetSubRect(cv::Mat& outM, const SRS22::Rect& region) {
        // current image is CV_8UC3
        OpenCVHelpers::CVGetSubRectRGB(vidHelper.currentImage, outM, region);
    }


}
