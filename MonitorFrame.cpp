#include "MonitorFrame.h"
#include "Settings.h"
#include "StringConversionHelpers.h"
#include "GlobalWorld.h"
#include "SRSUnitDisplay.h"
#include <wx/dcclient.h>
#include "convertmattowxbmp.h"
#include "TimeHelpers.h"

namespace SRS22 {

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

	void MonitorFrame::LoadMapChoices() {
		std::shared_ptr<Brain> b = GlobalWorld::GlobalWorldInstance.brains[0];
		ViewMapChoice->Clear();
		ViewMapChoice->AppendString(wxString("None"));
		for (auto m : b->conceptMaps) {
			ViewMapChoice->AppendString(wxString(m.first));
		}
	}

	void MonitorFrame::OnMonitorWindowActivate(wxActivateEvent& event) {

	}

	void MonitorFrame::OnMonitorWindowActivateApp(wxActivateEvent& event) {

	}

	void MonitorFrame::OnMonitorWindowClose(wxCloseEvent& event) {
		GlobalWorld::GlobalWorldInstance.Exit();
		exit(0);
	}

	void MonitorFrame::OnMonitorWindowHibernate(wxActivateEvent& event) {

	}

	void MonitorFrame::OnMonitorWindowIconize(wxIconizeEvent& event) {

	}

	void MonitorFrame::OnMonitorWindowIdle(wxIdleEvent& event) {

	}


	void MonitorFrame::OnNewMapMonitorWindow(wxCommandEvent& event) {

	}

	void MonitorFrame::RefreshMapMonitor(long long timeTicks) {
		if (ViewMapChoice->GetSelection() > 0) {
			auto m = GlobalWorld::GlobalWorldInstance.GetBrain(0)->FindMapByName(ViewMapChoice->GetStringSelection());
			auto M = m.value()->M;
			auto chgs = M.charges;
			int w = chgs.cols;
			int h = chgs.rows;
			if (chgs.dims == 3) {
				w = chgs.size[2];
				h = chgs.size[1];
			}
			wxBitmap bitmap(w, h, 24);
			ConvertMatBitmapTowxBitmap_CV_32FC1(m.value()->M.charges, w, h, bitmap);
			chosenMapBitmap->SetBitmap(bitmap);
			chosenMapBitmap->Refresh();
		}
		else {
			wxBitmap bitmap(64, 64, 24);
			chosenMapBitmap->SetBitmap(bitmap);
		}
		lastMapMonitorRefreshTime = timeTicks;
	}

	void MonitorFrame::OnMapChoiceChange(wxCommandEvent& event) {
		RefreshMapMonitor(SRS22::GetTimeTicksMs());
	}

	void MonitorFrame::OnRunToggleButton(wxCommandEvent& event) {
		if (event.IsChecked())
			GlobalWorld::GlobalWorldInstance.GetBrain(0)->Continue();
		else
			GlobalWorld::GlobalWorldInstance.GetBrain(0)->Pause();
	}

	void MonitorFrame::OnStep(wxCommandEvent& event) {
		RunButton->SetValue(true);
		GlobalWorld::GlobalWorldInstance.GetBrain(0)->DoSingleStep();
	}

	void MonitorFrame::OnContinueButton(wxCommandEvent& event) {
		RunButton->SetValue(true);
		GlobalWorld::GlobalWorldInstance.GetBrain(0)->Continue();
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

	void MonitorFrame::OnMonitorFrameTickTimer(wxTimerEvent& event) {
		// Milliseconds since the epoc.
		long long timeTicks = SRS22::GetTimeTicksMs();
		auto brain0 = GlobalWorld::GlobalWorldInstance.GetBrain(0);

		std::string s = "Tick Count: ";
		TickCountText->SetLabelText(s + std::to_string(brain0->tickCount));

		GlobalWorld::GlobalWorldInstance.TickAll();
		if (RunButton->GetValue()) {
			topVideoFrame->TakeImage(*brain0);
		}

		if (lastMapMonitorRefreshTime + mapMonitorRefreshDelay->GetValue() < timeTicks) {
			RefreshMapMonitor(timeTicks);
		}
	}

	void MonitorFrame::OnTestAClicked(wxCommandEvent& event) {
	}

	void MonitorFrame::OnTestBClicked(wxCommandEvent& event) {
	}

	void MonitorFrame::OnScrollMapMonitorMsSlider(wxScrollEvent& event) {
		RefreshMapMonitor(GetTimeTicksMs());
		wxString ss;
		refreshDelayMSText->SetLabel(ss.Format(wxT("Refresh %d ms."), mapMonitorRefreshDelay->GetValue()));
	}

	void MonitorFrame::OnPaintFrame(wxPaintEvent& event) {
		//wxClientDC dc(this);
		// draw some text
		//dc.DrawText(wxT("Testing"), 40, 60);
	}

}
