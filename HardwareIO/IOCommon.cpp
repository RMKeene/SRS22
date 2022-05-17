#include "../pch.h"

#include "IOCommon.h"

namespace SRS22 {

	std::map<std::string, IOCommon*>* IOCommon::globalIOTable;

	IOCommon::IOCommon(std::string ioClassName) : ioClassName(ioClassName) {
		if (getGlobalIOTable().find(ioClassName) != getGlobalIOTable().end())
			throw std::logic_error(std::string("Duplicate IOCommon ioClassName. Not allowed. ioClassName=") + ioClassName);
		getGlobalIOTable()[ioClassName] = this;
	}

	IOCommon::~IOCommon() {

	}

	bool IOCommon::Init() {
		return true;
	}

	void IOCommon::Shutdown() {

	}

	void IOCommon::PreTick() {

	}

	void IOCommon::PostTick() {

	}

	void IOCommon::UnitTest() {

	}
}
