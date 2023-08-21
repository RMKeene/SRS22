#include "CameraInIO.h"
#include "../OpenCVHelpers.h"
#include "CameraAttnSpotIO.h"
#include "../Maps/Camera/CameraFoveaMap.h"
#include "../OpenCVHelpers.h"

namespace SRS22 {
	using namespace cv;



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
		currentFrame = Mat(3, sizes, CV_32FC1);
		previousFrame = Mat(3, sizes, CV_32FC1);

		int sizesLowRes[3] = { 3,
			(int)(h * VideoHelper::lowResScale),
			(int)(w * VideoHelper::lowResScale) };
		currentFrameLowRes = Mat(3, sizesLowRes, CV_32FC1);
		previousFrameLowRes = Mat(3, sizesLowRes, CV_32FC1);

		int sizesFovea[3] = { 3, CameraFoveaMap_Height, CameraFoveaMap_Height };
		fovea = Mat(3, sizesFovea, CV_32FC1);
		foveaAbsDifference = Mat(3, sizesFovea, CV_32FC1);
		foveaAngles = Mat(3, sizesFovea, CV_32FC1);
		foveaCentricity = Mat(3, sizesFovea, CV_32FC1);
		foveaColorHistogram = Mat(3, sizesFovea, CV_32FC1);
		foveaEdges = Mat(3, sizesFovea, CV_32FC1);
		foveaRoughness = Mat(3, sizesFovea, CV_32FC1);

		return true;
	}

	void CameraInIO::Shutdown() {
		vidHelper.Shutdown();
		IOCommon::Shutdown();
	}

	void CameraInIO::PreTickHardwareAndIO() {
		IOCommon::PreTickHardwareAndIO();
		AcquireFrame();

		CameraAttnSpotIO* foveaIO = IOCommon::GetIO<CameraAttnSpotIO>();

		Rect r(foveaIO->GetRect());
		currentFoveaRect = r;
		GetSubRect(fovea, r);
		fovea = fovea.clone();
		std::string info = OpenCVHelpers::CVMatrixInfo(fovea);

		Mat red(fovea.size[1], fovea.size[1], CV_32FC1);
		Mat green(fovea.size[1], fovea.size[1], CV_32FC1);
		Mat blue(fovea.size[1], fovea.size[1], CV_32FC1);
		OpenCVHelpers::ExtractPlanes32FC1(fovea, red, green, blue);

		cv::Sobel(red, foveaEdges, CV_32FC1, 1, 1);

		OpenCVHelpers::error_aware_imwrite_imshow("./keene.jpg", foveaEdges, true);
	}

	void CameraInIO::PostTickHardwareAndUI() {
		IOCommon::PostTickHardwareAndUI();
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
		// Convert RGB uchar data to float 3 planes.
		// Thus 8UC3 2D to 32FC1 2D
		OpenCVHelpers::CVCopyRGBToMat(vidHelper.currentImage3UC8, currentFrame);
		OpenCVHelpers::CVCopyRGBToMat(vidHelper.previousImage3UC8, previousFrame);
		OpenCVHelpers::CVCopyRGBToMat(vidHelper.currentImageLowRes3UC8, currentFrameLowRes);
		OpenCVHelpers::CVCopyRGBToMat(vidHelper.previousImageLowRes3UC8, previousFrameLowRes);

		//std::string ss1 = OpenCVHelpers::CVMatrixInfo(currentFrame);
		//std::string ss2 = OpenCVHelpers::CVMatrixInfo(previousFrame);
		//std::string ss3 = OpenCVHelpers::CVMatrixInfo(currentFrameLowRes);
		//std::string ss4 = OpenCVHelpers::CVMatrixInfo(previousFrameLowRes);
		//std::string ss5 = OpenCVHelpers::CVMatrixInfo(currentAbsDifferenceLowRes);

		if (currentFrameLowRes.empty() == false &&
			previousFrameLowRes.empty() == false) {
			absdiff(currentFrameLowRes, previousFrameLowRes, currentAbsDifferenceLowRes);
		}
		return true;
	}

	void CameraInIO::GetSubRect(cv::Mat& outM, const SRS22::Rect& region) {
		// current image is CV_8UC3
		OpenCVHelpers::CVGetSubRectRGB(vidHelper.currentImage3UC8, outM, region);
	}
}