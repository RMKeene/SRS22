#include "MonitorFrame.h"
#include "Settings.h"

MonitorFrame::MonitorFrame(wxWindow* parent) : 
	MonitorFrameGen(parent) {
	whiteboardFrame = new WhiteboardFrame(this);
	whiteboardFrame->Show(true);
	topTextFrame = new TopTextFrame(this);
	topTextFrame->Show(true);
	topVideoFrame = new TopVideoFrame(this);
	topVideoFrame->Show(true);
}

MonitorFrame::~MonitorFrame() {

}

void MonitorFrame::OnRunToggleButton(wxCommandEvent& event) {

}

void MonitorFrame::OnStep(wxCommandEvent& event) {

}

void MonitorFrame::OnSaveLayoutButton(wxCommandEvent& event) {

}

void MonitorFrame::OnReloadLayoutButton(wxCommandEvent& event) {

}

void MonitorFrame::OnResetLayoutButton(wxCommandEvent& event) {
	SetPosition(wxPoint(10, 10));
	topTextFrame->SetPosition(wxPoint(50, 50));
	topTextFrame->Show();
	topTextFrame->Raise();
	whiteboardFrame->SetPosition(wxPoint(90, 90));
	whiteboardFrame->Show();
	whiteboardFrame->Raise();
	topVideoFrame->SetPosition(wxPoint(230, 230));
	topVideoFrame->Show();
	topVideoFrame->Raise();
}

void MonitorFrame::OnAudioInDeviceChoiceChanged(wxCommandEvent& event) {

}

void MonitorFrame::OnAudioVolumeIn(wxScrollEvent& event) {

}

void MonitorFrame::OnAudioOutDeviceChoiceChanged(wxCommandEvent& event) {

}

void MonitorFrame::OnAudioVolumeOut(wxScrollEvent& event) {

}

void MonitorFrame::OnVideoInChanged(wxCommandEvent& event) {

}

