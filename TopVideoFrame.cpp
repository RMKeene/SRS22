#include "pch.h"
#include "TopVideoFrame.h"

TopVideoFrame::TopVideoFrame(wxWindow* parent) :
	TopVideoFrameGen(parent) {

}

TopVideoFrame::~TopVideoFrame() {

}

void TopVideoFrame::OnClose(wxCloseEvent& event) {
	event.Veto();
}
