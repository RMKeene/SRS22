#include "SRS22LogTaker.h"

namespace SRS22 {

	SRS22LogTaker* SRS22LogTaker::globalLogTaker = nullptr;

	LogLevels SRS22LogTaker::loggingLevel = LogLevels::INFO;

	void SRS22LogTaker::SetLogTaker(SRS22LogTaker* logTaker) {
		globalLogTaker = logTaker;
	}

	void SRS22LogTaker::_TakeLog(std::string msg, LogLevels logLevel)
	{
		if (globalLogTaker == nullptr || (int)logLevel > loggingLevel)
			return;
		globalLogTaker->TakeLog(msg, logLevel);
	}

	void SRS22LogTaker::LogError(std::string msg) {
		_TakeLog(msg, LOG_ERROR);
	}

	void SRS22LogTaker::LogInfo(std::string msg) {
		_TakeLog(msg, INFO);
	}

	void SRS22LogTaker::LogDebug(std::string msg) {
		_TakeLog(msg, DEBUG);
	}

	void SRS22LogTaker::LogWarning(std::string msg) {
		_TakeLog(msg, WARNING);
	}

	void SRS22LogTaker::LogVerbose(std::string msg) {
		_TakeLog(msg, VERBOSE);
	}

	void SRS22LogTaker::LogMessage(std::string msg) {
		_TakeLog(msg, MESSAGE);
	}

	void SRS22LogTaker::LogTrace(std::string msg) {
		_TakeLog(msg, TRACE);
	}

	void SRS22LogTaker::LogStatus(std::string msg) {
		_TakeLog(msg, STATUS);
	}

	void SRS22LogTaker::LogSysError(std::string msg) {
		_TakeLog(msg, SYSERROR);
	}

	void SRS22LogTaker::LogFatalError(std::string msg) {
		_TakeLog(msg, FATAL_ERROR);
	}
}