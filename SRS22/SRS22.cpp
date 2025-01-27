// SRS22.cpp : Defines the class behaviors for the application.
//

#include "SRS22.h"
#include "ini.h"
#include "Settings.h"
#include <ppl.h>
#include "FastRand.h"

namespace SRS22 {

	MonitorFrame* SRS22App::monitorFrame = nullptr;
	SRS22App* SRS22App::srs22AppGlobal = nullptr;


	SRS22App::SRS22App() :
		// Locale affects on the language used in the calendar, and may affect
		// on the first day of the week.
		m_locale(wxLANGUAGE_DEFAULT)
	{
		srs22AppGlobal = this;
		SRS22LogTaker::SetLogTaker(this);
		Settings::globalSettings.Load();

		// Set max CPUs to 2 less than the number of cores.
		unsigned int numCores = std::thread::hardware_concurrency();
		unsigned int maxThreads = (numCores > 2) ? (numCores - 2) : 1; // Ensure at least 1 thread
		Concurrency::SchedulerPolicy policy(1, Concurrency::MaxConcurrency, maxThreads);
		Concurrency::CurrentScheduler::Create(policy);
	}

	SRS22App::~SRS22App() {
	}

	// `Main program' equivalent: the program execution "starts" here
	bool SRS22App::OnInit()
	{
		auto now = std::chrono::system_clock::now();
		auto duration = std::chrono::duration_cast<std::chrono::seconds>(now.time_since_epoch());
		setSeed((unsigned long)duration.count());

		if (!wxApp::OnInit())
			return false;

		monitorFrame = new MonitorFrame(nullptr);

		monitorFrame->LogRichText->Clear();

		wxLog::SetActiveTarget(new wxLogStderr());
		//wxLog::SetActiveTarget(new wxLogWindow(monitorFrame, "Log", true, false));

		SRS22LogTaker::LogInfo("SRS22App V0.1.0 Startup");

		monitorFrame->LoadMapChoices();
		monitorFrame->Show(true);

		// success: wxApp::OnRun() will be called which will enter the main message
		// loop and the application will run. If we returned false here, the
		// application would exit immediately.
		return true;
	}

	void SRS22App::TakeLog(std::string msg, LogLevels logLevel) {
		std::lock_guard<std::recursive_mutex> lock(SRS22LogTaker::logMutex);

		LogEntry logEntry;
		logEntry.msg = msg;
		logEntry.logLevel = logLevel;
		SRS22LogTaker::logQueue.push_back(logEntry);
	}

}