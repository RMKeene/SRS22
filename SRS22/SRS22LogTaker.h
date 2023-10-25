#pragma once

#include <string>

namespace SRS22 {

	/// <summary>
	/// Logging levels in order of severity
	/// </summary>
	enum LogLevels {
		FATAL_ERROR = 0,
		LOG_ERROR,
		SYSERROR,
		/// <summary>
		/// Status goes to the footer of some window in wxWidgets
		/// </summary>
		STATUS,
		MESSAGE,
		WARNING,
		INFO,
		DEBUG,
		VERBOSE,
		TRACE,
	};

	struct LogEntry {
		std::string msg;
		LogLevels logLevel;
	};


	/// <summary>
	/// An interface for anything that can receive and process a log entry.
	/// E.g. the MonitorWindow of the UI app, or any other logging.
	/// </summary>
	class SRS22LogTaker {
	public:
		virtual void TakeLog(std::string msg, LogLevels logLevel) = 0;

		static SRS22LogTaker* globalLogTaker;
		static LogLevels loggingLevel;

		static std::recursive_mutex logMutex;
		static std::list<LogEntry> logQueue;

		static void SetLogTaker(SRS22LogTaker* logTaker);

		static void _TakeLog(std::string msg, LogLevels logLevel);

		static void LogError(std::string msg);
		static void LogInfo(std::string msg);
		static void LogDebug(std::string msg);
		static void LogWarning(std::string msg);
		static void LogVerbose(std::string msg);
		static void LogMessage(std::string msg);
		static void LogTrace(std::string msg);
		static void LogStatus(std::string msg);
		static void LogSysError(std::string msg);
		static void LogFatalError(std::string msg);
	};
}


