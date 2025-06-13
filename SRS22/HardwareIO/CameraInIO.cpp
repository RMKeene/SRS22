#include "CameraInIO.h"
#include "../OpenCVHelpers.h"
#include "CameraAttnSpotIO.h"
#include "../Maps/Camera/CameraFoveaArray.h"
#include "../OpenCVHelpers.h"

namespace SRS22 {
	using namespace cv;

	CameraInIO::FoveaBundle::FoveaBundle(Mat fovea32F3) {
		red32F = Mat(fovea32F3.size[1], fovea32F3.size[2], CV_32FC1);
		green32F = Mat(fovea32F3.size[1], fovea32F3.size[2], CV_32FC1);
		blue32F = Mat(fovea32F3.size[1], fovea32F3.size[2], CV_32FC1);

		OpenCVHelpers::ExtractPlanes32FC1_3PlaneTo32FC1x3(fovea32F3, red32F, green32F, blue32F);
		red32F.convertTo(red8U, CV_8UC1, 255.0);
		green32F.convertTo(green8U, CV_8UC1, 255.0);
		blue32F.convertTo(blue8U, CV_8UC1, 255.0);
	}

	void CameraInIO::FoveaBundle::TakeBack32F(cv::Mat red32, cv::Mat green32, cv::Mat blue32) {
		red32F = red32.clone();
		green32F = green32.clone();
		blue32F = blue32.clone();
		red32F.convertTo(red8U, CV_8UC1, 255.0);
		green32F.convertTo(green8U, CV_8UC1, 255.0);
		blue32F.convertTo(blue8U, CV_8UC1, 255.0);
	}

	Mat CameraInIO::FoveaBundle::GetOut32F3Clone() {

		Mat out(red32F.cols, red32F.rows, CV_32FC1);
		OpenCVHelpers::CombinePlanes32FC1x3to32FC1_3Plane(red32F, green32F, blue32F, out);
		return out.clone();
	}

	CameraInIO::CameraInIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
		prepRotatedLines();
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
		currentAbsDifferenceLowRes = Mat(3, sizesLowRes, CV_32FC1);

		// 3, 15, 15
		int sizesFovea[3] = { 3, CameraFoveaArray_Height, CameraFoveaArray_Height };
		fovea = Mat(3, sizesFovea, CV_32FC1);
		foveaBlurred = Mat(3, sizesFovea, CV_32FC1);
		foveaAbsDifference = Mat(3, sizesFovea, CV_32FC1);

		foveaAngles000 = Mat(3, sizesFovea, CV_32FC1);
		foveaAngles225 = Mat(3, sizesFovea, CV_32FC1);
		foveaAngles450 = Mat(3, sizesFovea, CV_32FC1);
		foveaAngles675 = Mat(3, sizesFovea, CV_32FC1);
		foveaAngles900 = Mat(3, sizesFovea, CV_32FC1);
		foveaAngles1125 = Mat(3, sizesFovea, CV_32FC1);
		foveaAngles1350 = Mat(3, sizesFovea, CV_32FC1);
		foveaAngles1575 = Mat(3, sizesFovea, CV_32FC1);

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

		// Get the raw camera frame, then extract various concepts of the frame and fovea.
		CameraAttnSpotIO* foveaIO = IOCommon::GetIO<CameraAttnSpotIO>();

		foveaPreviousFrame = fovea.clone();

		Rect r(foveaIO->GetRect());
		currentFoveaRect = r;
		Rect centeredSmallR = Rect(r.CenterX() - CameraFoveaArray_Height / 2, r.CenterY() - CameraFoveaArray_Height / 2, CameraFoveaArray_Height, CameraFoveaArray_Height);
		GetSubRect(fovea, centeredSmallR);
		fovea = fovea.clone();
		std::string info = OpenCVHelpers::CVMatrixInfo(fovea);

		FoveaBundle foveaBundle(fovea);

		float foveaCX = r.halfW();
		float foveaCY = r.halfH();

		Mat foveaBlurredRed32FC1;
		Mat foveaBlurredGreen32FC1;
		Mat foveaBlurredBlue32FC1;
		foveaBundle.Allocate32FCSpaces(foveaBlurredRed32FC1, foveaBlurredGreen32FC1, foveaBlurredBlue32FC1);
		cv::GaussianBlur(foveaBundle.red32F, foveaBlurredRed32FC1, cv::Size(3, 3), 0.0);
		cv::GaussianBlur(foveaBundle.green32F, foveaBlurredGreen32FC1, cv::Size(3, 3), 0.0);
		cv::GaussianBlur(foveaBundle.blue32F, foveaBlurredBlue32FC1, cv::Size(3, 3), 0.0);
		FoveaBundle foveaBundleBlurred(foveaBlurred);
		foveaBundleBlurred.TakeBack32F(foveaBlurredRed32FC1, foveaBlurredGreen32FC1, foveaBlurredBlue32FC1);

		Mat cannyRed, cannyGreen, cannyBlue;
		foveaBundle.Allocate8UCSpaces(cannyRed, cannyGreen, cannyBlue);
		cv::Canny(foveaBundle.red8U, cannyRed, 100, 200);
		cv::Canny(foveaBundle.green8U, cannyGreen, 100, 200);
		cv::Canny(foveaBundle.blue8U, cannyBlue, 100, 200);
		OpenCVHelpers::Combine8UC1x3To32FC1_3Plane(cannyRed, cannyGreen, cannyBlue, foveaEdges);

		Mat foveaAnglesRed000, foveaAnglesGreen000, foveaAnglesBlue000;
		Mat foveaAnglesRed225, foveaAnglesGreen225, foveaAnglesBlue225;
		Mat foveaAnglesRed450, foveaAnglesGreen450, foveaAnglesBlue450;
		Mat foveaAnglesRed675, foveaAnglesGreen675, foveaAnglesBlue675;
		Mat foveaAnglesRed900, foveaAnglesGreen900, foveaAnglesBlue900;
		Mat foveaAnglesRed1125, foveaAnglesGreen1125, foveaAnglesBlue1125;
		Mat foveaAnglesRed1350, foveaAnglesGreen1350, foveaAnglesBlue1350;
		Mat foveaAnglesRed1575, foveaAnglesGreen1575, foveaAnglesBlue1575;

		foveaBundle.Allocate8UCSpaces(foveaAnglesRed000, foveaAnglesGreen000, foveaAnglesBlue000);
		foveaBundle.Allocate8UCSpaces(foveaAnglesRed225, foveaAnglesGreen225, foveaAnglesBlue225);
		foveaBundle.Allocate8UCSpaces(foveaAnglesRed450, foveaAnglesGreen450, foveaAnglesBlue450);
		foveaBundle.Allocate8UCSpaces(foveaAnglesRed675, foveaAnglesGreen675, foveaAnglesBlue675);
		foveaBundle.Allocate8UCSpaces(foveaAnglesRed900, foveaAnglesGreen900, foveaAnglesBlue900);
		foveaBundle.Allocate8UCSpaces(foveaAnglesRed1125, foveaAnglesGreen1125, foveaAnglesBlue1125);
		foveaBundle.Allocate8UCSpaces(foveaAnglesRed1350, foveaAnglesGreen1350, foveaAnglesBlue1350);
		foveaBundle.Allocate8UCSpaces(foveaAnglesRed1575, foveaAnglesGreen1575, foveaAnglesBlue1575);
		cv::filter2D(foveaBundle.red8U, foveaAnglesRed000, -1, rotatedLines000_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.green8U, foveaAnglesGreen000, -1, rotatedLines000_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.blue8U, foveaAnglesBlue000, -1, rotatedLines000_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.red8U, foveaAnglesRed225, -1, rotatedLines225_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.green8U, foveaAnglesGreen225, -1, rotatedLines225_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.blue8U, foveaAnglesBlue225, -1, rotatedLines225_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.red8U, foveaAnglesRed450, -1, rotatedLines450_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.green8U, foveaAnglesGreen450, -1, rotatedLines450_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.blue8U, foveaAnglesBlue450, -1, rotatedLines450_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.red8U, foveaAnglesRed675, -1, rotatedLines675_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.green8U, foveaAnglesGreen675, -1, rotatedLines675_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.blue8U, foveaAnglesBlue675, -1, rotatedLines675_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.red8U, foveaAnglesRed900, -1, rotatedLines900_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.green8U, foveaAnglesGreen900, -1, rotatedLines900_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.blue8U, foveaAnglesBlue900, -1, rotatedLines900_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.red8U, foveaAnglesRed1125, -1, rotatedLines1125_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.green8U, foveaAnglesGreen1125, -1, rotatedLines1125_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.blue8U, foveaAnglesBlue1125, -1, rotatedLines1125_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.red8U, foveaAnglesRed1350, -1, rotatedLines1350_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.green8U, foveaAnglesGreen1350, -1, rotatedLines1350_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.blue8U, foveaAnglesBlue1350, -1, rotatedLines1350_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.red8U, foveaAnglesRed1575, -1, rotatedLines1575_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.green8U, foveaAnglesGreen1575, -1, rotatedLines1575_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		cv::filter2D(foveaBundle.blue8U, foveaAnglesBlue1575, -1, rotatedLines1575_7x7_32FC1, cv::Point(-1, -1), 0.0, BORDER_CONSTANT);
		for (int y = 0; y < foveaAnglesRed000.size[0]; y++) {
			for (int x = 0; x < foveaAnglesRed000.size[1]; x++) {
				std::string a = OpenCVHelpers::CVMatrixInfo(foveaAngles000);
				std::string b = OpenCVHelpers::CVMatrixInfo(foveaAnglesRed000);
				foveaAngles000.at<float>(0, y, x) = foveaAnglesRed000.at<uchar>(y, x) / 255.0f;
				foveaAngles000.at<float>(1, y, x) = foveaAnglesGreen000.at<uchar>(y, x) / 255.0f;
				foveaAngles000.at<float>(2, y, x) = foveaAnglesBlue000.at<uchar>(y, x) / 255.0f;
				foveaAngles225.at<float>(0, y, x) = foveaAnglesRed225.at<uchar>(y, x) / 255.0f;
				foveaAngles225.at<float>(1, y, x) = foveaAnglesGreen225.at<uchar>(y, x) / 255.0f;
				foveaAngles225.at<float>(2, y, x) = foveaAnglesBlue225.at<uchar>(y, x) / 255.0f;
				foveaAngles450.at<float>(0, y, x) = foveaAnglesRed450.at<uchar>(y, x) / 255.0f;
				foveaAngles450.at<float>(1, y, x) = foveaAnglesGreen450.at<uchar>(y, x) / 255.0f;
				foveaAngles450.at<float>(2, y, x) = foveaAnglesBlue450.at<uchar>(y, x) / 255.0f;
				foveaAngles675.at<float>(0, y, x) = foveaAnglesRed675.at<uchar>(y, x) / 255.0f;
				foveaAngles675.at<float>(1, y, x) = foveaAnglesGreen675.at<uchar>(y, x) / 255.0f;
				foveaAngles675.at<float>(2, y, x) = foveaAnglesBlue675.at<uchar>(y, x) / 255.0f;
				foveaAngles900.at<float>(0, y, x) = foveaAnglesRed900.at<uchar>(y, x) / 255.0f;
				foveaAngles900.at<float>(1, y, x) = foveaAnglesGreen900.at<uchar>(y, x) / 255.0f;
				foveaAngles900.at<float>(2, y, x) = foveaAnglesBlue900.at<uchar>(y, x) / 255.0f;
				foveaAngles1125.at<float>(0, y, x) = foveaAnglesRed1125.at<uchar>(y, x) / 255.0f;
				foveaAngles1125.at<float>(1, y, x) = foveaAnglesGreen1125.at<uchar>(y, x) / 255.0f;
				foveaAngles1125.at<float>(2, y, x) = foveaAnglesBlue1125.at<uchar>(y, x) / 255.0f;
				foveaAngles1350.at<float>(0, y, x) = foveaAnglesRed1350.at<uchar>(y, x) / 255.0f;
				foveaAngles1350.at<float>(1, y, x) = foveaAnglesGreen1350.at<uchar>(y, x) / 255.0f;
				foveaAngles1350.at<float>(2, y, x) = foveaAnglesBlue1350.at<uchar>(y, x) / 255.0f;
				foveaAngles1575.at<float>(0, y, x) = foveaAnglesRed1575.at<uchar>(y, x) / 255.0f;
				foveaAngles1575.at<float>(1, y, x) = foveaAnglesGreen1575.at<uchar>(y, x) / 255.0f;
				foveaAngles1575.at<float>(2, y, x) = foveaAnglesBlue1575.at<uchar>(y, x) / 255.0f;
			}
		}

		absdiff(fovea, foveaPreviousFrame, foveaAbsDifference);

		// https://docs.opencv.org/3.4/d4/d70/tutorial_hough_circle.html
		Mat circlesRed, circlesGreen, circlesBlue;
		std::vector<Vec3f> circles;
		HoughCircles(foveaBundleBlurred.red8U, circles, HOUGH_GRADIENT, 
			1, /* db, ratio of accumulator to image size. */
			2 /* min dist between circles */,
			100 /* Canny edge detector high threshold */,
			30 /* Circle center detection thresh. Small is more false hits, higher is less hits but may miss some circles. */,
			2 /* min circle radius */, 
			64 /* max circle radius */);
		// Now make bright spots where circle centers are but only if the centers are very near the fovea center.
		for (Vec3f i : circles) {
			// i is X, Y, Radius
			if (abs(i[0] - foveaCX) < 2 && abs(i[1] - foveaCY) < 2) {
				
			}
		}

		OpenCVHelpers::Combine8UC1x3To32FC1_3Plane(cannyRed, cannyGreen, cannyBlue, foveaEdges);


		//OpenCVHelpers::error_aware_imwrite_imshow("./keene.jpg", foveaEdges, true);
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
		std::string ss5 = OpenCVHelpers::CVMatrixInfo(currentAbsDifferenceLowRes);

		if (currentFrameLowRes.empty() == false &&
			previousFrameLowRes.empty() == false) {
			absdiff(currentFrameLowRes, previousFrameLowRes, currentAbsDifferenceLowRes);
		}
		std::string ss5a = OpenCVHelpers::CVMatrixInfo(currentAbsDifferenceLowRes);
		return true;
	}

	void CameraInIO::GetSubRect(cv::Mat& outM, const SRS22::Rect& region) {
		// current image is CV_8UC3
		OpenCVHelpers::CVGetSubRectRGB(vidHelper.currentImage3UC8, outM, region);
	}

	/// <summary>
	/// Prepares the rotated line kernels for the fovea convolution.
	/// rotatedLines000_7x7_32FC1 etc.
	/// </summary>
	void CameraInIO::prepRotatedLines() {
		const int sz = 7;

		rotatedLines000_7x7_32FC1 = cv::Mat::zeros(sz, sz, CV_32FC1);
		rotatedLines225_7x7_32FC1 = cv::Mat::zeros(sz, sz, CV_32FC1);
		rotatedLines450_7x7_32FC1 = cv::Mat::zeros(sz, sz, CV_32FC1);
		rotatedLines675_7x7_32FC1 = cv::Mat::zeros(sz, sz, CV_32FC1);
		rotatedLines900_7x7_32FC1 = cv::Mat::zeros(sz, sz, CV_32FC1);
		rotatedLines1125_7x7_32FC1 = cv::Mat::zeros(sz, sz, CV_32FC1);
		rotatedLines1350_7x7_32FC1 = cv::Mat::zeros(sz, sz, CV_32FC1);
		rotatedLines1575_7x7_32FC1 = cv::Mat::zeros(sz, sz, CV_32FC1);

		// 0 degrees
		rotatedLines000_7x7_32FC1.at<float>(3, 3) = 1.0; // Center dot.
		for (int n = 1; n <= 3; n++) {
			//                                  Y    X
			rotatedLines000_7x7_32FC1.at<float>(3, 3 + n) = 1.0f;
			rotatedLines000_7x7_32FC1.at<float>(3, 3 - n) = 1.0f;
		}
		// 22.5 degrees
		rotatedLines225_7x7_32FC1.at<float>(3, 3) = 1.0; // Center dot.
		for (int n = 1; n <= 3; n++) {
			//                                    Y        X
			rotatedLines225_7x7_32FC1.at<float>(3 + n / 2, 3 + n) = 1.0f;
			rotatedLines225_7x7_32FC1.at<float>(3 - n / 2, 3 - n) = 1.0f;
		}
		// 45 degrees
		rotatedLines450_7x7_32FC1.at<float>(3, 3) = 1.0; // Center dot.
		for (int n = 1; n <= 3; n++) {
			//                                    Y      X
			rotatedLines450_7x7_32FC1.at<float>(3 + n, 3 + n) = 1.0f;
			rotatedLines450_7x7_32FC1.at<float>(3 - n, 3 - n) = 1.0f;
		}
		// 67.5 degrees
		rotatedLines675_7x7_32FC1.at<float>(3, 3) = 1.0; // Center dot.
		for (int n = 1; n <= 3; n++) {
			//                                    Y      X
			rotatedLines675_7x7_32FC1.at<float>(3 + n, 3 + n / 2) = 1.0f;
			rotatedLines675_7x7_32FC1.at<float>(3 - n, 3 - n / 2) = 1.0f;
		}
		// 90 degrees
		rotatedLines900_7x7_32FC1.at<float>(3, 3) = 1.0; // Center dot.
		for (int n = 1; n <= 3; n++) {
			//                                    Y    X
			rotatedLines900_7x7_32FC1.at<float>(3 + n, 3) = 1.0f;
			rotatedLines900_7x7_32FC1.at<float>(3 - n, 3) = 1.0f;
		}
		// 112.5 degrees
		for (int n = 1; n <= 3; n++) {
			//                                     Y        X
			rotatedLines1125_7x7_32FC1.at<float>(3 + n, 3 - n / 2) = 1.0f;
			rotatedLines1125_7x7_32FC1.at<float>(3 - n, 3 + n / 2) = 1.0f;
		}
		// 135 degrees
		for (int n = 1; n <= 3; n++) {
			//                                     Y      X
			rotatedLines1350_7x7_32FC1.at<float>(3 + n, 3 - n) = 1.0f;
			rotatedLines1350_7x7_32FC1.at<float>(3 - n, 3 + n) = 1.0f;
		}
		// 157.5 degrees
		for (int n = 1; n <= 3; n++) {
			//                                     Y          X
			rotatedLines1575_7x7_32FC1.at<float>(3 + n / 2, 3 - n) = 1.0f;
			rotatedLines1575_7x7_32FC1.at<float>(3 - n / 2, 3 + n) = 1.0f;
		}
	}

	/// <summary>
	/// For debug and validation displays the fovea convolution kernels.
	/// E.g. rotatedLines000_7x7_32FC1 etc.
	/// </summary>
	void CameraInIO::imShowFoveaConvolutionKernels() {
		cv::Mat m(7, 7, CV_8UC1);
		OpenCVHelpers::Convert32FC1To8UC1(rotatedLines000_7x7_32FC1, m);
		imshow("Fovea Kernel Rotated Line 0.0 deg", m);
		OpenCVHelpers::Convert32FC1To8UC1(rotatedLines225_7x7_32FC1, m);
		imshow("Fovea Kernel Rotated Line 22.5 deg", m);
		OpenCVHelpers::Convert32FC1To8UC1(rotatedLines450_7x7_32FC1, m);
		imshow("Fovea Kernel Rotated Line 45.0 deg", m);
		OpenCVHelpers::Convert32FC1To8UC1(rotatedLines675_7x7_32FC1, m);
		imshow("Fovea Kernel Rotated Line 67.5 deg", m);
		OpenCVHelpers::Convert32FC1To8UC1(rotatedLines900_7x7_32FC1, m);
		imshow("Fovea Kernel Rotated Line 90.0 deg", m);
		OpenCVHelpers::Convert32FC1To8UC1(rotatedLines1125_7x7_32FC1, m);
		imshow("Fovea Kernel Rotated Line 112.5 deg", m);
		OpenCVHelpers::Convert32FC1To8UC1(rotatedLines1350_7x7_32FC1, m);
		imshow("Fovea Kernel Rotated Line 135.0 deg", m);
		OpenCVHelpers::Convert32FC1To8UC1(rotatedLines1575_7x7_32FC1, m);
		imshow("Fovea Kernel Rotated Line 157.5 deg", m);
	}
}