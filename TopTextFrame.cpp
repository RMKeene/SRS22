#include "TopTextFrame.h"

namespace SRS22 {

	TopTextFrame::TopTextFrame(wxWindow* parent) :
		TopTextFrameGen(parent) {

	}

	TopTextFrame::~TopTextFrame() {

	}

	void TopTextFrame::OnClose(wxCloseEvent& event) {
		event.Veto();
	}

}