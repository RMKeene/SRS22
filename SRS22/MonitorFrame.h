#pragma once
#include "SRS22UIgen.h"
#include "TopTextFrame.h"
#include "WhiteboardFrame.h"
#include "TopVideoFrame.h"
#include "source/UISettings.h"

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
		void OnGoodClicked(wxCommandEvent& event) override;
		void OnBadClicked(wxCommandEvent& event) override;
		void DoLoad(wxCommandEvent& event) override;
		void DoStore(wxCommandEvent& event) override;
		void OnAudioInDeviceChoiceChanged(wxCommandEvent& event) override;
		void OnAudioVolumeIn(wxScrollEvent& event) override;
		void OnAudioOutDeviceChoiceChanged(wxCommandEvent& event) override;
		void OnAudioVolumeOut(wxScrollEvent& event) override;
		void OnVideoInChanged(wxCommandEvent& event) override;
		void OnMonitorFrameTickTimer(wxTimerEvent& event) override;
		void OnNewMapMonitorWindow(wxCommandEvent& event) override;
		void OnMapChoiceChange(wxCommandEvent& event) override;
		void OnFreezeFoveaCB(wxCommandEvent& event)  override;
		void OnFreezeScreenAttnSpotCB(wxCommandEvent& event) override;
		void OnTestAClicked(wxCommandEvent& event) override;
		void OnTestBClicked(wxCommandEvent& event) override;
		void OnScrollMapMonitorMsSlider(wxScrollEvent& event) override;
		void OnNeuronFactorsChangeUpdateClicked(wxCommandEvent& event) override;
		void OnRevertNeuronFactorsClicked(wxCommandEvent& event) override;
		void OnNeuronFactorsDefaultsClicked(wxCommandEvent& event) override;

		void OnPaintFrame(wxPaintEvent& event) override;

		void RefreshMapMonitor(long long timeTicks);

		void ProcessLogQueueInWindowThread();

		void CreateUISettingsElements();
		void CortexSettingsToUI();

		/***
		* Convert the text value from textCtrl to a float into value. False if fails and value remains unchanged.
		* Also on fail to parse sets background pink, on success sets background white.
		*/
		bool ToFloat(wxTextCtrl* textCtrl, float * value);

		TopTextFrame* topTextFrame;
		WhiteboardFrame* whiteboardFrame;
		TopVideoFrame* topVideoFrame;

		long long lastMapMonitorRefreshTime = 0;

		bool hasSetupVideoInDroplist = false;

		std::string brainFileName;

		/// <summary>
		/// Key is the SRSetting's Name.  The value is the setting's UI element that we created on startup.
		/// </summary>
		std::map<std::string, LabeledTextCtrl *> settingsUiElements;
	};
}
