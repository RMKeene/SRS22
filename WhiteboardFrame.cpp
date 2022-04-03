#include "pch.h"
#include "WhiteboardFrame.h"

WhiteboardFrame::WhiteboardFrame(wxWindow* parent) :
	WhiteboardFrameGen(parent) {
	wxBitmap bm = wxBitmap(wxT("IDB_WHITEBMP16"), wxBITMAP_TYPE_RESOURCE);
}

WhiteboardFrame::~WhiteboardFrame() {

}

void WhiteboardFrame::OnClose(wxCloseEvent& event) {
	event.Veto();
}

void WhiteboardFrame::OnWhiteButton(wxCommandEvent& event) {
	whiteboardBrush = wxBrush(wxColour(255, 255, 255, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
}

void WhiteboardFrame::OnBlackButton(wxCommandEvent& event) {
	whiteboardBrush = wxBrush(wxColour(0, 0, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
}

void WhiteboardFrame::OnRedButton(wxCommandEvent& event) {
	whiteboardBrush = wxBrush(wxColour(255, 0, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
}

void WhiteboardFrame::OnGreenButton(wxCommandEvent& event) {
	whiteboardBrush = wxBrush(wxColour(0, 255, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
}

void WhiteboardFrame::OnBlueButton(wxCommandEvent& event) {
	whiteboardBrush = wxBrush(wxColour(0, 0, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
}

void WhiteboardFrame::OnYellowButton(wxCommandEvent& event) {
	whiteboardBrush = wxBrush(wxColour(255, 255, 0, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
}

void WhiteboardFrame::OnCyanButton(wxCommandEvent& event) {
	whiteboardBrush = wxBrush(wxColour(0, 255, 255, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
}

void WhiteboardFrame::OnMagentaButton(wxCommandEvent& event) {
	whiteboardBrush = wxBrush(wxColour(255, 0, 255, wxALPHA_OPAQUE), wxBRUSHSTYLE_SOLID);
}


