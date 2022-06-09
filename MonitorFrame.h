#pragma once
#include "SRS22UIgen.h"
#include "TopTextFrame.h"
#include "WhiteboardFrame.h"
#include "TopVideoFrame.h"
#include "HardwareIO/WaveInputHelper.h"
#include "HardwareIO/WaveOutputHelper.h"

namespace SRS22 {
	class MonitorFrame :
		public MonitorFrameGen
	{
	public:
		MonitorFrame(wxWindow* parent);
		~MonitorFrame();

		void LoadMapChoices();

		void OnMonitorWindowActivate(wxActivateEvent& event) override;
		void OnMonitorWindowActivateApp(wxActivateEvent& event) override;
		void OnMonitorWindowClose(wxCloseEvent& event) override;
		void OnMonitorWindowHibernate(wxActivateEvent& event) override;
		void OnMonitorWindowIconize(wxIconizeEvent& event) override;
		void OnMonitorWindowIdle(wxIdleEvent& event) override;

		void OnRunToggleButton(wxCommandEvent& event) override;
		void OnStep(wxCommandEvent& event) override;
		void OnContinueButton(wxCommandEvent& event) override;
		void OnSaveLayoutButton(wxCommandEvent& event) override;
		void OnReloadLayoutButton(wxCommandEvent& event) override;
		void OnResetLayoutButton(wxCommandEvent& event) override;
		void OnAudioInDeviceChoiceChanged(wxCommandEvent& event) override;
		void OnAudioVolumeIn(wxScrollEvent& event) override;
		void OnAudioOutDeviceChoiceChanged(wxCommandEvent& event) override;
		void OnAudioVolumeOut(wxScrollEvent& event) override;
		void OnVideoInChanged(wxCommandEvent& event) override;
		void OnMonitorFrameTickTimer(wxTimerEvent& event) override;
		void OnNewMapMonitorWindow(wxCommandEvent& event) override;
		void OnMapChoiceChange(wxCommandEvent& event) override;
		void OnTestAClicked(wxCommandEvent& event) override;
		void OnTestBClicked(wxCommandEvent& event) override;
		void OnScrollMapMonitorMsSlider(wxScrollEvent& event) override;

		void OnPaintFrame(wxPaintEvent& event) override;

		void RefreshMapMonitor(long long timeTicks);

		TopTextFrame* topTextFrame;
		WhiteboardFrame* whiteboardFrame;
		TopVideoFrame* topVideoFrame;

		long long lastMapMonitorRefreshTime = 0;
	};
}

