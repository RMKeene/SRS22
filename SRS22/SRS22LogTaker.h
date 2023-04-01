#pragma once

#include <string>

namespace SRS22 {

	enum LogLevels {
		INFO = 0,
		WARNING = 1,
		LOG_ERROR = 2,
		VERBOSE = 3,
		STATUS = 4,
		SYSERROR = 5,
		TRACE = 6,
		MESSAGE = 7,
		FATAL_ERROR = 8,
		DEBUG = 9,
	};


	/// <summary>
	/// An interface for anything that can receive and process a log entry.
	/// E.g. the MonitorWindow of the UI app, or any other logging.
	/// </summary>
	class SRS22LogTaker {
	public:
		virtual void TakeLog(std::string msg, LogLevels logLevel) = 0;
	};

	static SRS22LogTaker* globalLogTaker = nullptr;

	static void SetLogTaker(SRS22LogTaker* logTaker) {
		globalLogTaker = logTaker;
	}

	static void TakeLog(std::string msg, LogLevels logLevel)
	{
		if (globalLogTaker == nullptr)
			return;
		globalLogTaker->TakeLog(msg, logLevel);
	}

	static void LogError(std::string msg) {
		TakeLog(msg, LOG_ERROR);
	}

	static void LogInfo(std::string msg) {
		TakeLog(msg, INFO);
	}

	static void LogDebug(std::string msg) {
		TakeLog(msg, DEBUG);
	}

	static void LogWarning(std::string msg) {
		TakeLog(msg, WARNING);
	}

	static void LogVerbose(std::string msg) {
		TakeLog(msg, VERBOSE);
	}

	static void LogMessage(std::string msg) {
		TakeLog(msg, MESSAGE);
	}

	static void LogTrace(std::string msg) {
		TakeLog(msg, TRACE);
	}

	static void LogStatus(std::string msg) {
		TakeLog(msg, STATUS);
	}

	static void LogSysError(std::string msg) {
		TakeLog(msg, SYSERROR);
	}

	static void LogFatalError(std::string msg) {
		TakeLog(msg, FATAL_ERROR);
	}
}


