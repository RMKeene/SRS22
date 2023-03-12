#include "WhiteboardInIO.h"

namespace SRS22 {
	std::recursive_mutex WhiteboardInIO::mtx;
	std::list<WhiteboardPt> WhiteboardInIO::inputQueue;

	WhiteboardInIO::WhiteboardInIO() : IOCommon() {
		IOCOMMON_SETCLASSNAME;
	}

	WhiteboardInIO::~WhiteboardInIO() {
	}

	bool WhiteboardInIO::Init() {
		IOCommon::Init();
		return true;
	}

	void WhiteboardInIO::Shutdown() {
		IOCommon::Shutdown();
	}

	void WhiteboardInIO::PreTickHardwareAndIO() {
		IOCommon::PreTickHardwareAndIO();
	}

	void WhiteboardInIO::PostTickHardwareAndUI() {
		IOCommon::PostTickHardwareAndUI();
	}

	void WhiteboardInIO::UnitTest() {
	}
}