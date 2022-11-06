#include "TopTextFrame.h"
#include "HardwareIO/TextInIO.h"
#include "HardwareIO/TextOutIO.h"
#include "GlobalWorld.h"

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
		TextIn->Clear();
		BrainH br = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		br->textIn.TakeClearInput();
	}

	void TopTextFrame::OnTextInChar(wxKeyEvent& event) {
		// Not working for Japanese and such. Pretty much just ASCII.
		BrainH br = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		auto kk = event.GetKeyCode();
		br->textIn.TakeCharacterInput((TextIOType)kk);
		event.Skip();
	}

	void TopTextFrame::OnTextOutClearButton(wxCommandEvent& event) {
		TextOut->Clear();
	}
}