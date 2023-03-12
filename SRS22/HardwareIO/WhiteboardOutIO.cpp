#include "WhiteboardOutIO.h"

namespace SRS22 {
	std::recursive_mutex WhiteboardOutIO::mtx;
	std::list<WhiteboardPt> WhiteboardOutIO::outputQueue;

	WhiteboardOutIO::WhiteboardOutIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	WhiteboardOutIO::~WhiteboardOutIO() {
	}

	bool WhiteboardOutIO::Init() {
		IOCommon::Init();
		return true;
	}

	void WhiteboardOutIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void WhiteboardOutIO::PreTickHardwareAndIO() {
		IOCommon::PreTickHardwareAndIO();
	}

	void WhiteboardOutIO::PostTickHardwareAndUI() {
		IOCommon::PostTickHardwareAndUI();
	}

	void WhiteboardOutIO::UnitTest() {
	}
}