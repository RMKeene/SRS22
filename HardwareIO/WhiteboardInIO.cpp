#include "WhiteboardInIO.h"

namespace SRS22 {
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

	void WhiteboardInIO::PreTick() {
		IOCommon::PreTick();
	}

	void WhiteboardInIO::PostTick() {
		IOCommon::PostTick();
	}

	void WhiteboardInIO::UnitTest() {
	}
}