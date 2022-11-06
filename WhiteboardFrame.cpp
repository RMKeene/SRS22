#include "WhiteboardFrame.h"

namespace SRS22 {
	WhiteboardFrame::WhiteboardFrame(wxWindow* parent) :
		WhiteboardFrameGen(parent),
		canvas(this, wxID_ANY, wxPoint(0, 0), wxSize(740, 460)) {
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
}