#include "TopVideoFrame.h"
#include "Brain.h"

using namespace cv;

namespace SRS22 {

	TopVideoFrame::TopVideoFrame(wxWindow* parent) :
		TopVideoFrameGen(parent), 
		canvas(this, wxID_ANY, wxPoint(0, 0), wxSize(640, 480)) {
		TopVideoFrameVertLayout->Add(&canvas);
	}

	TopVideoFrame::~TopVideoFrame() {
	}

	void TopVideoFrame::OnActivate(wxActivateEvent& event) {
	}

	void TopVideoFrame::OnClose(wxCloseEvent& event) {
		event.Veto();
	}

	void TopVideoFrame::TakeImage(Brain& brain) {
		cv::Size sz = brain.cameraInput.getCurrentImage().size();
		int imageWidth = sz.width;
		int imageHeight = sz.height;
		if(imageWidth > 0 && imageHeight > 0) {
			wxImage Image(imageWidth, imageHeight, brain.cameraInput.getCurrentImage().data, TRUE);
			canvas.backingStore = Image;
			canvas.Refresh();
		}
	}

}
