#include "pch.h"
#include "WhiteboardFrame.h"

WhiteboardFrame::WhiteboardFrame(wxWindow* parent) :
	WhiteboardFrameGen(parent) {

}

WhiteboardFrame::~WhiteboardFrame() {

}

void WhiteboardFrame::OnClose(wxCloseEvent& event) {
	event.Veto();
}
