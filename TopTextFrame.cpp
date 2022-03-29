#include "pch.h"
#include "TopTextFrame.h"

TopTextFrame::TopTextFrame(wxWindow* parent) :
	TopTextFrameGen(parent) {

}

TopTextFrame::~TopTextFrame() {

}

void TopTextFrame::OnClose(wxCloseEvent& event) {
	event.Veto();
}
