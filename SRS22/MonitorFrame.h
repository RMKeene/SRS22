#pragma once
#include "SRS22UIgen.h"
#include "TopTextFrame.h"
#include "WhiteboardFrame.h"
#include "TopVideoFrame.h"
#include "source/UISettings.h"
#include "CortexSettings.h" 
#include "TopStatsFrame.h"

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
		void OnUpdateCortexFactorsClicked(wxCommandEvent& event) override;
		void OnLoadCortexSettingsClicked(wxCommandEvent& event) override;
		void OnUndoNeuronFactorsClicked(wxCommandEvent& event) override;
		void OnSaveCortexSaveButton(wxCommandEvent& event) override;
		void OnDefaultsCortexSettingsClicked(wxCommandEvent& event) override;

		void OnPaintFrame(wxPaintEvent& event) override;

		void RefreshMapMonitor(long long timeTicks);

		void ProcessLogQueueInWindowThread();

		void CreateUISettingsElements();
		void CreateSettingUiElement(CortexSettings::SRSSetting& setting);
		wxBoxSizer* GetSettingParent(CortexSettings::SRSSetting& setting);
		void CortexSettingsToUI();
		void CortexSettingFromUI(wxBoxSizer* sizer, CortexSettings::SRSSetting& setting);
		void OnSettingTextEnter(wxCommandEvent& event);
		void OnSettingTextUpdated(wxCommandEvent& event);

		/**
		 * Pops up a file chooser dialog for opening (reading) a file.
		 * @param title The dialog title.
		 * @param directory The initial directory.
		 * @param pattern The file type pattern (e.g., "*.txt").
		 * @param defaultFileName Optional default file name.
		 * @return The selected file path, or empty string if cancelled.
		 */
		static std::string PopupFileChooserForRead(const std::string& title, const std::string& directory, const std::string& pattern, const std::string& defaultFileName = "");

		/**
		 * Pops up a file chooser dialog for saving (writing) a file.
		 * @param title The dialog title.
		 * @param directory The initial directory.
		 * @param pattern The file type pattern (e.g., "*.txt").
		 * @param defaultFileName Optional default file name.
		 * @return The selected file path, or empty string if cancelled.
		 */
		static std::string PopupFileChooserForWrite(const std::string& title, const std::string& directory, const std::string& pattern, const std::string& defaultFileName = "");
		/***
		* Convert the text value from textCtrl to a float into value. False if fails and value remains unchanged.
		* Also on fail to parse sets background pink, on success sets background white.
		*/
		bool ToFloat(wxTextCtrl* textCtrl, float* value);

		TopTextFrame* topTextFrame;
		WhiteboardFrame* whiteboardFrame;
		TopVideoFrame* topVideoFrame;
		TopStatsFrame* topStatsFrame;

		long long lastMapMonitorRefreshTime = 0;

		bool hasSetupVideoInDroplist = false;

		std::string brainFileName;

		/// <summary>
		/// Key is the SRSetting's Name.  The value is the setting's UI element that we created on startup.
		/// </summary>
		std::map<std::string, LabeledTextCtrl*> settingsUiElements;
	};
}
