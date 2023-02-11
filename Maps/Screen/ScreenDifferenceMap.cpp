#include "../../pch.h"
#include "ScreenDifferenceMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenInputIO.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"

namespace SRS22 {
	ScreenDifferenceMap::ScreenDifferenceMap(Brain* br) :
		ConceptMap(br, MapUidE::SCREENDIFFERENCE_MAP, "ScreenDifferenceMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, ScreenInputIO::AbsDiffHeight, ScreenInputIO::AbsDiffWidth,
			"A low resolution version of the screen view processed for frame to frame motion differences.") {
		SetDecayFactors(false);
	}

	ScreenDifferenceMap::~ScreenDifferenceMap() {
	}

	void ScreenDifferenceMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto screenIn = IOCommon::GetIO<ScreenInputIO>();
		// currentAbsDifferenceLowRes is 8UC4 format so we convert.
		if (screenIn->currentAbsDifferenceLowRes.empty() == false) {
			for (int y = 0; y < nextM.matSize()[1]; y++) {
				for (int x = 0; x < nextM.matSize()[2]; x++) {
					nextM.charges.at<float>(0, y, x) = (float)screenIn->currentAbsDifferenceLowRes.at<cv::Vec4b>(y, x)[0] / 255.0f;
					nextM.charges.at<float>(1, y, x) = (float)screenIn->currentAbsDifferenceLowRes.at<cv::Vec4b>(y, x)[1] / 255.0f;
					nextM.charges.at<float>(2, y, x) = (float)screenIn->currentAbsDifferenceLowRes.at<cv::Vec4b>(y, x)[2] / 255.0f;
				}
			}
		}
	}

	void ScreenDifferenceMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}