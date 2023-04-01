// SRS22.cpp : Defines the class behaviors for the application.
//

#include "SRS22.h"
#include "ini.h"
#include "Settings.h"

namespace SRS22 {

	MonitorFrame* SRS22App::monitorFrame = nullptr;

	SRS22App::SRS22App() :
		// Locale affects on the language used in the calendar, and may affect
		// on the first day of the week.
		m_locale(wxLANGUAGE_DEFAULT)
	{
		SRS22::SetLogTaker(this);
		Settings::globalSettings.Load();
	}

	SRS22App::~SRS22App() {
	}

	// `Main program' equivalent: the program execution "starts" here
	bool SRS22App::OnInit()
	{
		if (!wxApp::OnInit())
			return false;

		monitorFrame = new MonitorFrame(nullptr);

		monitorFrame->LogRichText->Clear();
		wxLog::SetActiveTarget(new wxLogStderr());
		//wxLog::SetActiveTarget(new wxLogWindow(monitorFrame, "Log", true, false));
		LogInfo("SRS22App V0.1.0 Startup");

		monitorFrame->LoadMapChoices();
		monitorFrame->Show(true);

		// success: wxApp::OnRun() will be called which will enter the main message
		// loop and the application will run. If we returned false here, the
		// application would exit immediately.
		return true;
	}

	void SRS22App::TakeLog(std::string msg, LogLevels logLevel) {
		switch (logLevel) {
		case LOG_ERROR:
			wxLogError("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(255, 0, 0));
			break;
		case DEBUG:
			wxLogDebug("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(0, 255, 0));
			break;
		case INFO:
			wxLogInfo("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(0, 0, 255));
			break;
		case WARNING:
			wxLogWarning("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(255, 255, 0));
			break;
		case VERBOSE:
			wxLogVerbose("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(255, 255, 255));
			break;
		case MESSAGE:
			wxLogMessage("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(0, 255, 255));
			break;
		case TRACE:
			wxLogTrace("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(255, 0, 255));
			break;
		case STATUS:
			wxLogStatus("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(255, 0, 255));
			break;
		case SYSERROR:
			wxLogSysError("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(255, 0, 255));
			break;
		case FATAL_ERROR:
			wxLogFatalError("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(255, 0, 255));
			break;
		default:
			wxLogInfo("%s", msg.c_str());
			monitorFrame->LogRichText->BeginTextColour(wxColor(128, 128, 128));
			break;
		}
		monitorFrame->LogRichText->WriteText(msg);
		monitorFrame->LogRichText->Newline();
		monitorFrame->LogRichText->EndTextColour();

	}
}