#include "TopVideoFrame.h"
#include "Brain.h"
#include "GlobalWorld.h"

using namespace cv;

namespace SRS22 {

	TopVideoFrame::TopVideoFrame(wxWindow* parent) :
		TopVideoFrameGen(parent), 
		canvas(this, wxID_ANY, wxPoint(0, 0), wxSize(640, 480)) {
		TopVideoFrameVertLayout->Add(&canvas);
		canvas.OnPaintPostListener = this;
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

	void TopVideoFrame::OnPostPaint(wxPaintDC* DC, wxPaintEvent& event) {
		DC->SetPen(*wxRED_PEN);
		
		// Outer whole fovea area rectangle
		CameraAttnSpotIO* io = IOCommon::GetIO<CameraAttnSpotIO>();
		DC->SetBrush(*wxTRANSPARENT_BRUSH);
		DC->DrawRectangle(io->GetRect().toWxRect());

		/// <summary>
		/// Inner central detail area.
		/// </summary>
		/// <param name="DC"></param>
		/// <param name="event"></param>
		const SRS22::Point ctr = io->GetPt();
		auto brain = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		auto cameraFoveaMapOptional = brain->FindMapByName("CameraFoveaMap");
		auto cameraFoveaMap = cameraFoveaMapOptional.value();
		wxRect cfr(ctr.X - cameraFoveaMap->Width() / 2, ctr.Y - cameraFoveaMap->Height() / 2,
			cameraFoveaMap->Width(), cameraFoveaMap->Height());
		DC->DrawRectangle(cfr);
	}

}
