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
		
		int sizes[3] = { 3, h, w };
		currentFrame = cv::Mat(3, sizes, CV_32FC1);
		previousFrame = cv::Mat(3, sizes, CV_32FC1);
		
		int sizesLowRes[3] = { 3,
			(int)(h * VideoHelper::lowResScale),
			(int)(w * VideoHelper::lowResScale) };
		currentFrameLowRes = cv::Mat(3, sizesLowRes, CV_32FC1);
		previousFrameLowRes = cv::Mat(3, sizesLowRes, CV_32FC1);
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
		if (!vidHelper.CaptureFrame())
			return false;
		OpenCVHelpers::CVCopyRGBToMat(vidHelper.currentImage3UC8, currentFrame);
		OpenCVHelpers::CVCopyRGBToMat(vidHelper.previousImage3UC8, previousFrame);
		OpenCVHelpers::CVCopyRGBToMat(vidHelper.currentImageLowRes3UC8, currentFrameLowRes);
		OpenCVHelpers::CVCopyRGBToMat(vidHelper.previousImageLowRes3UC8, previousFrameLowRes);

		if (currentFrameLowRes.empty() == false &&
			previousFrameLowRes.empty() == false) {
			cv::absdiff(currentFrameLowRes, previousFrameLowRes, currentAbsDifferenceLowRes);
		}
		return true;
	}

	void CameraInIO::GetSubRect(cv::Mat& outM, const SRS22::Rect& region) {
		// current image is CV_8UC3
		OpenCVHelpers::CVGetSubRectRGB(vidHelper.currentImage3UC8, outM, region);
	}


}
