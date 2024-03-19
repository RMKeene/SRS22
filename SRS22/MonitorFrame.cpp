#include "MonitorFrame.h"
#include "GlobalWorld.h"
#include "convertmattowxbmp.h"
#include "TimeHelpers.h"
#include "OpenCVHelpers.h"
#include "ConceptMap.h"

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
		BrainH b = GlobalWorld::GlobalWorldInstance.brains[0];
		ViewMapChoice->Clear();
		ViewMapChoice->AppendString(wxString("None"));
		for (auto m : b->conceptMapsByName) {
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
			auto charges = mv->M;
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
			SelectedMapDetailLabel->SetLabel(OpenCVHelpers::MapUIText(mv->M));
		}
		else {
			wxBitmap bitmap(64, 64, 24);
			chosenMapBitmap->SetBitmap(bitmap);
			chosenMapText1->SetLabelText("No Map");
			chosenMapText2->SetLabelText("Selected");
			SelectedMapDetailLabel->SetLabel("Map Info:");
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
	// TODO - Seperate the Brains onto their own threads.
	// See https://randomascii.wordpress.com/2020/10/04/windows-timer-resolution-the-great-rule-change/
	void MonitorFrame::OnMonitorFrameTickTimer(wxTimerEvent& event) {
		ProcessLogQueueInWindowThread();
		// Milliseconds since the epoc.
		long long timeTicks = SRS22::GetTimeTicksMs();

		BrainH brain0 = GlobalWorld::GlobalWorldInstance.GetBrain(0);

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