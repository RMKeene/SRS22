#include "VideoHelper.h"
#include <Mmsystem.h>

namespace SRS22 {

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
		previousImage = currentImage;
		*cap >> currentImage;
		if (!currentImage.empty()) {
			//cv::String ts = cv::typeToString(currentImage.type()); // "CV_8UC3"
			//imshow(ts, currentImage);

			cv::Size sz = currentImage.size();
			int imageWidth = sz.width;
			int imageHeight = sz.height;
			cv::cvtColor(currentImage, currentImage, cv::COLOR_RGB2BGR);
			return true;
		}
		return false;
	}

}
