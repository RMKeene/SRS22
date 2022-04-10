#include "TopVideoFrame.h"

using namespace cv;

namespace SRS22 {

	TopVideoFrame::TopVideoFrame(wxWindow* parent) :
		TopVideoFrameGen(parent), 
		canvas(this, wxID_ANY, wxPoint(0, 0), wxSize(640, 480)) {
		TopVideoFrameVertLayout->Add(&canvas);
	}

	TopVideoFrame::~TopVideoFrame() {
		if (cap)
			cap->release();
	}

	void TopVideoFrame::OnActivate(wxActivateEvent& event) {
	}

	void TopVideoFrame::OnClose(wxCloseEvent& event) {
		event.Veto();
	}

	void TopVideoFrame::TakeImage() {
		if (cap == nullptr)
			cap = new VideoCapture(0);
		if (!cap->isOpened()) { 
			return;
		}

		// 640 x 480 color CV_8UC3 depth 24 bits BGR
		previousImage = currentImage;
		*cap >> currentImage; 
		if (!currentImage.empty()) {
			// cv::String ts = cv::typeToString(currentImage.type());
			//imshow("SRS22 Video & Audio", currentImage);

			cv::Size sz = currentImage.size();
			int imageWidth = sz.width;
			int imageHeight = sz.height;
			cv::cvtColor(currentImage, currentImage, cv::COLOR_RGB2BGR);
			wxImage Image(imageWidth, imageHeight, currentImage.data, TRUE);
			canvas.backingStore = Image;
			canvas.Refresh();
		}
	}

}
