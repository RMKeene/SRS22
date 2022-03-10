#include "pch.h"
#include "ScreenIn.h"

namespace SRS22 {

	ScreenIn::ScreenIn(ConnectivityTriple ctrip, cv::Vec3f location, int w) : SRSUnit(ctrip, location, w) {
	}

	ScreenIn::ScreenIn(ConnectivityTriple ctrip, cv::Vec3f location, int w, int h) :
		SRSUnit(ctrip, location, w, h) {

	}

	ScreenIn::ScreenIn(ConnectivityTriple ctrip, cv::Vec3f location, int w, int h, int d) :
		SRSUnit(ctrip, location, w, h, d) {

	}

	ScreenIn::~ScreenIn() {

	}

}
