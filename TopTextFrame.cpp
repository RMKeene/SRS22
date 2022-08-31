#include "TopTextFrame.h"
#include "HardwareIO/TextInIO.h"
#include "HardwareIO/TextOutIO.h"

namespace SRS22 {

	TopTextFrame::TopTextFrame(wxWindow* parent) :
		TopTextFrameGen(parent) {

	}

	TopTextFrame::~TopTextFrame() {

	}

	void TopTextFrame::OnClose(wxCloseEvent& event) {
		event.Veto();
	}

	void TopTextFrame::OnTextInClearButton(wxCommandEvent& event) {

	}

	void TopTextFrame::OnInputTextKeyDown(wxKeyEvent& event) {

	}

	void TopTextFrame::OnInputText(wxCommandEvent& event) {

	}

	void TopTextFrame::OnInputTextEnter(wxCommandEvent& event) {

	}

	void TopTextFrame::OnInputTextMaxLen(wxCommandEvent& event) {

	}

	void TopTextFrame::OnTextOutClearButton(wxCommandEvent& event) {

	}


}