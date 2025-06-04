#include "MonitorFrame.h"
#include "GlobalWorld.h"
#include "convertmattowxbmp.h"
#include "TimeHelpers.h"
#include "OpenCVHelpers.h"
#include "ConceptMap.h"
#include "Cortex.h"

namespace SRS22 {
	MonitorFrame::MonitorFrame(wxWindow* parent) :
		MonitorFrameGen(parent) {
		BrainH b = GlobalWorld::GlobalWorldInstance.brains[0];

		brainFileName = "brain.srs";
		whiteboardFrame = new WhiteboardFrame(this);
		whiteboardFrame->Show(true);
		topTextFrame = new TopTextFrame(this);
		topTextFrame->Show(true);
		topVideoFrame = new TopVideoFrame(this);
		topVideoFrame->Show(true);

		CreateUISettingsElements();
	}

	MonitorFrame::~MonitorFrame() {
	}

	void MonitorFrame::LoadMapChoices() {
		BrainH b = GlobalWorld::GlobalWorldInstance.brains[0];
		ViewMapChoice->Clear();
		ViewMapChoice->AppendString(wxString("None"));
		for (auto& m : b->conceptMapsByName) {
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
		// Note that when the brain is active (not paused) this function is virtually never called.
	}

	void MonitorFrame::OnNewMapMonitorWindow(wxCommandEvent& event) {
	}

	void MonitorFrame::RefreshMapMonitor(long long timeTicks) {
		if (ViewMapChoice->GetSelection() > 0) {
			auto m = GlobalWorld::GlobalWorldInstance.GetBrain(0)->FindMapByName(ViewMapChoice->GetStringSelection());
			if (m.has_value() == false) // No such map.
				return;
			std::shared_ptr<ConceptMap> mv = m.value();
			auto& charges = mv->M;
			int w = charges.cols;
			int h = charges.rows;
			if (charges.dims == 3) {
				w = charges.size[2];
				h = charges.size[1];
			}

			float scaleX = 1.0f;
			float scaleY = 1.0f;
			if (w < 64) {
				scaleX = 64.0f / (float)w;
				w = 64;
			}
			if (h < 64) {
				scaleY = 64.0f / (float)h;
				h = 64;
			}

			if (charges.dims == 2 && charges.size[0] + charges.size[1] == 2 + 1) {
				if (m.value()->displayMode == SRSUnitDisplayModes::TWOVALUECAMERA) {
					w = w * 1.3;
				}
				else if (m.value()->displayMode == SRSUnitDisplayModes::TWOVALUEWIDESCREEN) {
					w = w * 1.8;
				}
				wxBitmap bitmap(w, h, 24);

				if (bitmap.GetWidth() != w || bitmap.GetHeight() != h) {
					chosenMapBitmap->SetSize(w, h);
					chosenMapBitmap->SetMaxSize(wxSize(w, h));
					chosenMapBitmap->SetMinSize(wxSize(w, h));
					this->Layout();
					this->Fit();
				}
				Convert2ValueMatBitmapTowxBitmap_CV_32FC1(charges, w, h, bitmap, 255.0f, scaleX, scaleY);
				chosenMapBitmap->SetBitmap(bitmap);
			}
			//else if (m.value()->displayMode == SRSUnitDisplayModes::BARGRAPH) {
			// TODO bar graph
			//}
			else {
				wxBitmap bitmap(w, h, 24);

				if (bitmap.GetWidth() != w || bitmap.GetHeight() != h) {
					chosenMapBitmap->SetSize(w, h);
					chosenMapBitmap->SetMaxSize(wxSize(w, h));
					chosenMapBitmap->SetMinSize(wxSize(w, h));
					this->Layout();
					this->Fit();
				}
				std::string ss = OpenCVHelpers::CVMatrixInfo(charges);
				if (charges.type() == CV_32FC1)
					ConvertMatBitmapTowxBitmap_CV_32FC1(charges, w, h, bitmap, 255.0f, scaleX, scaleY);

				chosenMapBitmap->SetBitmap(bitmap);
			}

			chosenMapBitmap->Refresh();

			wxString s;
			s << "[" << mv->Width() <<
				", " << mv->Height() <<
				", " << mv->Depth() << "]";
			chosenMapText1->SetLabelText(s);
			chosenMapText2->SetLabelText(mv->MapName);
			chosenMapText3->SetLabel(mv->MapDescription);
			//SelectedMapDetailLabel->SetLabel(OpenCVHelpers::MapUIText(mv->M));
		}
		else {
			wxBitmap bitmap(64, 64, 24);
			chosenMapBitmap->SetBitmap(bitmap);
			chosenMapText1->SetLabelText("No Map");
			chosenMapText2->SetLabelText("Selected");
			//SelectedMapDetailLabel->SetLabel("Map Info:");
		}
		lastMapMonitorRefreshTime = timeTicks;
	}

	void MonitorFrame::OnMapChoiceChange(wxCommandEvent& event) {
		RefreshMapMonitor(SRS22::GetTimeTicksMs());
	}

	void MonitorFrame::OnFreezeFoveaCB(wxCommandEvent& event) {
		CameraAttnSpotIO::freezeAttnSpotPosition = event.IsChecked();
	}

	void MonitorFrame::OnFreezeScreenAttnSpotCB(wxCommandEvent& event) {
		ScreenAttnSpotIO::freezeAttnSpotPosition = event.IsChecked();
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

	void MonitorFrame::OnGoodClicked(wxCommandEvent& event) {
		BrainH b = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		b->GoodJob();
	}

	void MonitorFrame::OnBadClicked(wxCommandEvent& event) {
		BrainH b = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		b->BadJob();
	}

	void MonitorFrame::DoLoad(wxCommandEvent& event) {
		BrainH b = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		pair<bool, string> r = b->Load(brainFileName);
		if (r.first == false)
			wxMessageBox(r.second, "Error", wxICON_ERROR);
		else {
			wxMessageBox("Brain loaded.", "Success", wxICON_INFORMATION);
			CortexSettingsToUI();
		}
	}

	void MonitorFrame::DoStore(wxCommandEvent& event) {
		BrainH b = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		if (b->Store(brainFileName))
			wxMessageBox("Brain stored.", "Success", wxICON_INFORMATION);
		else
			wxMessageBox("Error storing brain.", "Error", wxICON_ERROR);
	}

	void MonitorFrame::OnNeuronFactorsChangeUpdateClicked(wxCommandEvent& event) {
		BrainH b = GlobalWorld::GlobalWorldInstance.GetBrain(0);

	}

	bool MonitorFrame::ToFloat(wxTextCtrl* textCtrl, float* value) {
		wxString s = textCtrl->GetValue();
		double f = 0.0f;
		if (!s.ToDouble(&f)) {
			textCtrl->SetBackgroundColour(wxColor(255, 50, 50));
			return false;
		}
		textCtrl->SetBackgroundColour(wxColor(255, 255, 255));
		*value = (float)f;
		return true;
	}

	void MonitorFrame::OnNeuronFactorsDefaultsClicked(wxCommandEvent& event) {
		GlobalWorld::GlobalWorldInstance.GetBrain(0)->cortex->settings.SetValuesToDefaults();
	}

	void MonitorFrame::OnRevertNeuronFactorsClicked(wxCommandEvent& event) {
		CortexSettingsToUI();
	}

	void MonitorFrame::CreateUISettingsElements() {
		BrainH b = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		for (auto& setting : b->cortex->settings.settings) {
			CreateSettingUiElement(*setting.second);
		}
	}

	wxBoxSizer* MonitorFrame::GetSettingParent(CortexSettings::SRSSetting& setting) {
		switch (setting.SettingRow)
		{
		case 0:
			return m_SettingsH0;
		case 1:
			return m_SettingsH1;
		case 2:
			return m_SettingsH2;
		default:
			throw std::runtime_error("Invalid SettingRow for " + setting.Name +
				" row " + std::to_string(setting.SettingRow));
		}
	}

	void MonitorFrame::CreateSettingUiElement(CortexSettings::SRSSetting& setting) {
		wxBoxSizer* settingParent = GetSettingParent(setting);
		wxWindow* settingParentWindow = settingParent->GetContainingWindow();
		wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
		sizer->SetClientData((void*)&setting);
		setting.clientData = (void*)sizer;
		wxStaticText* label = new wxStaticText(m_SettingsVertPane->GetStaticBox(), wxID_ANY, setting.UILabel);
		wxTextCtrl* textCtrl = nullptr;
		if (setting.Type == CortexSettings::SettingType::F) {
			textCtrl = new wxTextCtrl(m_SettingsVertPane->GetStaticBox(), wxID_ANY, wxString::Format("%f", setting.Value.f),
				wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
		}
		else if (setting.Type == CortexSettings::SettingType::D) {
			textCtrl = new wxTextCtrl(m_SettingsVertPane->GetStaticBox(), wxID_ANY, wxString::Format("%f", setting.Value.d),
				wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
		}
		else if (setting.Type == CortexSettings::SettingType::I) {
			textCtrl = new wxTextCtrl(m_SettingsVertPane->GetStaticBox(), wxID_ANY, wxString::Format("%d", setting.Value.i),
				wxDefaultPosition, wxDefaultSize, wxTE_PROCESS_ENTER);
		}

		textCtrl->SetToolTip(setting.Name + " : " + setting.Description);

		sizer->Add(label, 0, wxALL, 5);
		sizer->Add(textCtrl, 0, wxALL | wxEXPAND, 5);
		settingParent->Add(sizer, 0, wxALL | wxEXPAND, 5);

		textCtrl->Connect(wxEVT_COMMAND_TEXT_UPDATED, wxCommandEventHandler(MonitorFrame::OnSettingTextUpdated), sizer, this);
		textCtrl->Connect(wxEVT_COMMAND_TEXT_ENTER, wxCommandEventHandler(MonitorFrame::OnSettingTextEnter), sizer, this);
	}

	void MonitorFrame::CortexSettingsToUI() {
		BrainH b = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		for (auto& setting : b->cortex->settings.settings) {
			wxBoxSizer* sizer = (wxBoxSizer*)setting.second->clientData;
			wxTextCtrl* textCtrl = (wxTextCtrl*)sizer->GetItem(1)->GetWindow();
			if (setting.second->Type == CortexSettings::SettingType::F) {
				textCtrl->SetValue(wxString::Format("%f", setting.second->Value.f));
			}
			else if (setting.second->Type == CortexSettings::SettingType::D) {
				textCtrl->SetValue(wxString::Format("%f", setting.second->Value.d));
			}
			else if (setting.second->Type == CortexSettings::SettingType::I) {
				textCtrl->SetValue(wxString::Format("%d", setting.second->Value.i));
			}
		}
	}

	void MonitorFrame::CortexSettingFromUI(wxBoxSizer* sizer, CortexSettings::SRSSetting& setting) {
		wxTextCtrl* textCtrl = (wxTextCtrl*)sizer->GetItem(1)->GetWindow();
		bool parseOk = false;
		if (setting.Type == CortexSettings::SettingType::F) {
			float f = 0.0f;
			parseOk = ToFloat(textCtrl, &f);
			if (parseOk) {
				setting.Value.f = f;
			}
		}
		else if (setting.Type == CortexSettings::SettingType::D) {
			double d = 0.0;
			parseOk = textCtrl->GetValue().ToDouble(&d);
			if (parseOk) {
				setting.Value.d = d;
			}
		}
		else if (setting.Type == CortexSettings::SettingType::I) {
			long i = 0;
			parseOk = textCtrl->GetValue().ToLong(&i);
			if (parseOk) {
				setting.Value.i = (int)i;
			}
		}
		// Set background color based on parse result
		if (!parseOk) {
			textCtrl->SetBackgroundColour(wxColor(255, 50, 50));
		}
		else {
			textCtrl->SetBackgroundColour(wxColor(255, 255, 255));
		}
		textCtrl->Refresh();
	}

	/// <summary>
	/// When they hit Enter in a text box in settings.
	/// </summary>
	/// <param name="event"></param>
	void MonitorFrame::OnSettingTextEnter(wxCommandEvent& event) {
		wxBoxSizer* sizer = (wxBoxSizer*)event.GetEventUserData();
		CortexSettings::SRSSetting& setting = *(CortexSettings::SRSSetting*)sizer->GetClientData();
		CortexSettingFromUI(sizer, setting);
	}

	/// <summary>
	/// When they press a key in a text box in settings.
	/// </summary>
	/// <param name="event"></param>
	void MonitorFrame::OnSettingTextUpdated(wxCommandEvent& event) {
		wxBoxSizer* sizer = (wxBoxSizer*)event.GetEventUserData();
		CortexSettings::SRSSetting& setting = *(CortexSettings::SRSSetting*)sizer->GetClientData();
		CortexSettingFromUI(sizer, setting);
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

	// On Windows the call sleep(1) will sleep from 1 to 15 ms. This Tick callback at the fastest gets called
	// about 10x per sec even if the interval set in wxWindows is less than 100ms.
	// TODO - Separate the Brains onto their own threads.
	// See https://randomascii.wordpress.com/2020/10/04/windows-timer-resolution-the-great-rule-change/
	void MonitorFrame::OnMonitorFrameTickTimer(wxTimerEvent& event) {
		ProcessLogQueueInWindowThread();
		// Milliseconds since the epoch.
		long long timeTicks = SRS22::GetTimeTicksMs();

		BrainH brain0 = GlobalWorld::GlobalWorldInstance.GetBrain(0);
		Cortex* cortex = brain0->cortex;

		brain0->doParallel = m_CPUParallelCB->GetValue();

		TickCountText->SetLabelText(wxString::Format("Ticks: %lld", brain0->tickCount));
		float intervalMs = (float)event.GetInterval();
		if (intervalMs > 0.0f) {
			brain0->ticksPerSecondLatest = (int)((brain0->tickCountRecent * 1000) / intervalMs);
			TicksPerSecondText->SetLabelText(wxString::Format("Ticks/Sec.: %d", brain0->ticksPerSecondLatest));
		}
		else {
			TicksPerSecondText->SetLabelText(wxString::Format("Ticks/Sec.: ---"));
		}
		brain0->tickCountRecent = 0;

		overallGoodnessLabel->SetLabelText(wxString::Format("Goodness: %6.4f  Change: %6.4f",
			brain0->overallGoodness,
			brain0->overallGoodnessRateOfChange));

		GlobalWorld::GlobalWorldInstance.TickAll();
		if (RunButton->GetValue()) {
			topVideoFrame->TakeImage(*brain0);
		}

		if (lastMapMonitorRefreshTime + mapMonitorRefreshDelay->GetValue() < timeTicks) {
			RefreshMapMonitor(timeTicks);
		}

		if (!hasSetupVideoInDroplist) {
			wxSleep(1);
			auto cameraIn = IOCommon::GetIO<CameraInIO>();
			cameraIn->vidHelper.EnumerateDevices();
			if (cameraIn && cameraIn->vidHelper.listedDevices.size() > 0) {
				VideoInChoiceDropbox->Clear();
				for (auto it = cameraIn->vidHelper.listedDevices.begin(); it != cameraIn->vidHelper.listedDevices.end(); it++) {
					VideoInChoiceDropbox->AppendString(*it);
				}
				VideoInChoiceDropbox->Select(0);
				hasSetupVideoInDroplist = true;
			}
		}

		if (WaveInputHelper::totalBytesIn < 4000) {
			lastInSizeText->SetLabelText(wxString::Format("Last In Size: %d, total %d", WaveInputHelper::lastPacketSize, WaveInputHelper::totalBytesIn));
		}
		else if (WaveInputHelper::totalBytesIn < 2000000) {
			lastInSizeText->SetLabelText(wxString::Format("Last In Size: %d, total %d k", WaveInputHelper::lastPacketSize, WaveInputHelper::totalBytesIn / 1024));
		}
		else {
			lastInSizeText->SetLabelText(wxString::Format("Last In Size: %d, total %d M", WaveInputHelper::lastPacketSize, WaveInputHelper::totalBytesIn / (1024 * 1024)));
		}

		MonitorStatisticsLine1->SetLabelText(wxString::Format("Total Neurons: %d, Connections %d, Fired: %d, Zeros %d, Ones %d, Fatigued %d, Stimulus %d",
			cortex->stats.countOfNeuronsProcessed, TOTAL_NEURONS * NEURON_UPSTREAM_LINKS, cortex->stats.countOfNeuronsFired, cortex->stats.countOfZeros,
			cortex->stats.countOfOnes, cortex->stats.countFatigued, cortex->stats.countStimulus));
		MonitorStatisticsLine2->SetLabelText(wxString::Format("ReRoutes: %d, Average C: %6.4f, Confidence: %6.4f",
			cortex->stats.countOfReRoutes, cortex->stats.averageNeuronCharge, cortex->stats.averageConfidence));
		MonitorStatisticsLine3->SetLabelText("Stats:");
	}

	void MonitorFrame::OnTestAClicked(wxCommandEvent& event) {
	}

	void MonitorFrame::OnTestBClicked(wxCommandEvent& event) {
		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->imShowFoveaConvolutionKernels();
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

	// Called in window idle
	void MonitorFrame::ProcessLogQueueInWindowThread() {
		std::lock_guard<std::recursive_mutex> lock(SRS22LogTaker::logMutex);
		if (SRS22LogTaker::logQueue.size() == 0)
			return;
		LogEntry logEntry = SRS22LogTaker::logQueue.back();
		SRS22LogTaker::logQueue.pop_back();

		switch (logEntry.logLevel) {
		case LogLevels::LOG_ERROR:
			wxLogError("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(255, 0, 0));
			break;
		case LogLevels::DEBUG:
			wxLogDebug("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(240, 255, 240));
			break;
		case LogLevels::INFO:
			wxLogInfo("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(240, 240, 255));
			break;
		case LogLevels::WARNING:
			wxLogWarning("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(255, 255, 220));
			break;
		case LogLevels::VERBOSE:
			wxLogVerbose("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(255, 255, 255));
			break;
		case LogLevels::MESSAGE:
			wxLogMessage("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(220, 255, 255));
			break;
		case LogLevels::TRACE:
			wxLogTrace("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(255, 220, 255));
			break;
		case LogLevels::STATUS:
			wxLogStatus("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(255, 220, 255));
			break;
		case LogLevels::SYSERROR:
			wxLogSysError("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(255, 200, 255));
			break;
		case LogLevels::FATAL_ERROR:
			wxLogFatalError("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(255, 190, 255));
			break;
		default:
			wxLogInfo("%s", logEntry.msg.c_str());
			LogRichText->BeginTextColour(wxColor(128, 128, 128));
			break;
		}

		LogRichText->SetCaretPosition(-1);
		LogRichText->SetInsertionPoint(0);
		LogRichText->WriteText(logEntry.msg);
		LogRichText->Newline();
		LogRichText->EndTextColour();
	}
}