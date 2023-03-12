#include "WhiteboardFrame.h"
#include "GlobalWorld.h"
#include "HardwareIO/WhiteboardOutIO.h"
#include "HardwareIO/WhiteboardInIO.h"
#include "HardwareIO/WhiteboardPt.h"

namespace SRS22 {
	WhiteboardFrame::WhiteboardFrame(wxWindow* parent) :
		WhiteboardFrameGen(parent),
		canvas(this, wxID_ANY, wxPoint(0, 0), wxSize(740, 460)) {
		canvas.OnDrawPixel = this;
		WhiteboardHorizPanel->Add(&canvas);
	}

	WhiteboardFrame::~WhiteboardFrame() {
	}

	void WhiteboardFrame::OnClose(wxCloseEvent& event) {
		event.Veto();
	}

	void WhiteboardFrame::OnWhiteButton(wxCommandEvent& event) {
		canvas.currentBrush = whiteboardBrush = wxBrush(wxColour(255, 255, 255, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
	}

	void WhiteboardFrame::OnBlackButton(wxCommandEvent& event) {
		canvas.currentBrush = whiteboardBrush = wxBrush(wxColour(0, 0, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
	}

	void WhiteboardFrame::OnRedButton(wxCommandEvent& event) {
		canvas.currentBrush = whiteboardBrush = wxBrush(wxColour(255, 0, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
	}

	void WhiteboardFrame::OnGreenButton(wxCommandEvent& event) {
		canvas.currentBrush = whiteboardBrush = wxBrush(wxColour(0, 255, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
	}

	void WhiteboardFrame::OnBlueButton(wxCommandEvent& event) {
		canvas.currentBrush = whiteboardBrush = wxBrush(wxColour(0, 0, 255, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
	}

	void WhiteboardFrame::OnYellowButton(wxCommandEvent& event) {
		canvas.currentBrush = whiteboardBrush = wxBrush(wxColour(255, 255, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
	}

	void WhiteboardFrame::OnCyanButton(wxCommandEvent& event) {
		canvas.currentBrush = whiteboardBrush = wxBrush(wxColour(0, 255, 255, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
	}

	void WhiteboardFrame::OnMagentaButton(wxCommandEvent& event) {
		canvas.currentBrush = whiteboardBrush = wxBrush(wxColour(255, 0, 255, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
	}

	void WhiteboardFrame::OnWhiteboardClearButton(wxCommandEvent& event) {
		canvas.Clear();
		canvas.Refresh();
	}

	// 20 per second.
	void WhiteboardFrame::OnTimerTick(wxTimerEvent& event) {
		BrainH br = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		WhiteboardPt pt;
		if (br->whiteboardOut.GetNextQueuedPt(pt)) {
			int x = static_cast<int>(std::clamp(pt.x * canvas.GetSize().x, 0.0f, (float)canvas.GetSize().x));
			int y = static_cast<int>(std::clamp(pt.y * canvas.GetSize().y, 0.0f, (float)canvas.GetSize().y));
			canvas.SetPixel(wxColor(pt.r, pt.g, pt.b, static_cast<unsigned char>(255.0f * pt.blend)), wxPoint(x, y), 1);
			canvas.Refresh();
		}
	}

	/// <summary>
	/// When the user draws a point on the whiteboard.
	/// </summary>
	/// <param name="c"></param>
	/// <param name="pt"></param>
	/// <param name="dotSize"></param>
	void WhiteboardFrame::OnDrawPixel(wxColor c, wxPoint pt, int dotSize) {
		BrainH br = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		WhiteboardPt Wpt(c.Red(), c.Green(), c.Blue(), 1.0f,
			std::clamp(pt.x / (float)canvas.GetSize().x, 0.0f, 1.0f),
			std::clamp(pt.y / (float)canvas.GetSize().y, 0.0f, 1.0f));

		br->whiteboardIn.EnqueuePoint(Wpt);
	}
}