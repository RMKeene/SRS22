#include "VideoHelper.h"
#include <Mmsystem.h>

namespace SRS22 {

	const float VideoHelper::lowResScale = 0.1f;

	VideoHelper::VideoHelper() {

	}

	VideoHelper::~VideoHelper() {
		Shutdown();
	}

	void VideoHelper::Shutdown() {
		if (cap) {
			cap->release();
			cap = nullptr;
		}
	}

	int VideoHelper::GetCameraWidthWin32() {
		if (cap == nullptr)
			cap = new VideoCapture(0);
		if (!cap->isOpened()) {
			return 0;
		}

		return cap->get(CAP_PROP_FRAME_WIDTH);
	}

	int VideoHelper::GetCameraHeightWin32() {
		if (cap == nullptr)
			cap = new VideoCapture(0);
		if (!cap->isOpened()) {
			return 0;
		}

		return cap->get(CAP_PROP_FRAME_HEIGHT);
	}

	bool VideoHelper::CaptureFrame() {
		if (cap == nullptr)
			cap = new VideoCapture(0);
		if (!cap->isOpened()) {
			return false;
		}

		// 640 x 480 color CV_8UC3 depth 24 bits BGR
		currentImage3UC8.copyTo(previousImage3UC8);
		currentImageLowRes3UC8.copyTo(previousImageLowRes3UC8);
		*cap >> currentImage3UC8;
		if (!currentImage3UC8.empty()) {
			//cv::String ts = cv::typeToString(currentImage.type()); // "CV_8UC3"
			//imshow(ts, currentImage);

			cv::Size sz = currentImage3UC8.size();
			int imageWidth = sz.width;
			int imageHeight = sz.height;
			cv::cvtColor(currentImage3UC8, currentImage3UC8, cv::COLOR_RGB2BGR);
			// Genertate low res RGB.
			cv::Size size(currentImage3UC8.cols * lowResScale, currentImage3UC8.rows * lowResScale);
			cv::resize(currentImage3UC8, currentImageLowRes3UC8, size);
			return true;
		}
		return false;
	}

}
