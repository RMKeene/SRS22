#pragma once
#include "SRS22UIgen.h"
#include "TopTextFrame.h"
#include "WhiteboardFrame.h"
#include "TopVideoFrame.h"
#include "WaveInputHelper.h"
#include "WaveOutputHelper.h"

namespace SRS22 {
	class MonitorFrame :
		public MonitorFrameGen
	{
	public:
		MonitorFrame(wxWindow* parent);
		~MonitorFrame();

		void OnRunToggleButton(wxCommandEvent& event) override;
		void OnStep(wxCommandEvent& event) override;
		void OnSaveLayoutButton(wxCommandEvent& event) override;
		void OnReloadLayoutButton(wxCommandEvent& event) override;
		void OnResetLayoutButton(wxCommandEvent& event) override;
		void OnAudioInDeviceChoiceChanged(wxCommandEvent& event) override;
		void OnAudioVolumeIn(wxScrollEvent& event) override;
		void OnAudioOutDeviceChoiceChanged(wxCommandEvent& event) override;
		void OnAudioVolumeOut(wxScrollEvent& event) override;
		void OnVideoInChanged(wxCommandEvent& event) override;
		void OnMonitorFrameTickTimer(wxTimerEvent& event) override;
		void OnTestAClicked(wxCommandEvent& event) override;
		void OnTestBClicked(wxCommandEvent& event) override;

		TopTextFrame* topTextFrame;
		WhiteboardFrame* whiteboardFrame;
		TopVideoFrame* topVideoFrame;
		WaveInputHelper waveInput;
		WaveOutputHelper waveOut;
	};
}

