#include "../../pch.h"

#include "IOCommon.h"

namespace SRS22 {
	std::map<std::string, IOCommon*>* IOCommon::globalIOTable;

	IOCommon::IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	IOCommon::~IOCommon() {
	}

	bool IOCommon::Init() {
		if (getGlobalIOTable().find(ioClassName) != getGlobalIOTable().end())
			throw std::logic_error(std::string("Duplicate IOCommon ioClassName. Not allowed. ioClassName=") + ioClassName);
		getGlobalIOTable()[ioClassName] = this;

		return true;
	}

	void IOCommon::Shutdown() {
	}

	void IOCommon::PreTickHardwareAndIO() {
	}

	void IOCommon::PostTickHardwareAndUI() {
	}

	void IOCommon::UnitTest() {
	}
}