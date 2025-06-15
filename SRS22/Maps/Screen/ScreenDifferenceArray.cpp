#include "../../SRS22pch.h"
#include "ScreenDifferenceArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenInputIO.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"
#include "../../SRSMath.h"

namespace SRS22 {
	ScreenDifferenceArray::ScreenDifferenceArray(Brain* br) :
		ConceptArray(br, ArrayUidE::SCREENDIFFERENCE_MAP, "ScreenDifferenceArray", NeuronType::IS_INPUT,
			3, ScreenInputIO::AbsDiffHeight, ScreenInputIO::AbsDiffWidth, 0.0f,
			"A low resolution version of the screen view processed for frame to frame motion differences.") {
	}

	ScreenDifferenceArray::~ScreenDifferenceArray() {
	}

	void ScreenDifferenceArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto screenIn = IOCommon::GetIO<ScreenInputIO>();
		// currentAbsDifferenceLowRes is 8UC4 format so we convert.
		if (screenIn->currentAbsDifferenceLowRes.empty() == false) {
			for (int y = 0; y < nextM.size[1]; y++) {
				for (int x = 0; x < nextM.size[2]; x++) {
					nextM.at<float>(0, y, x) = (float)screenIn->currentAbsDifferenceLowRes.at<cv::Vec4b>(y, x)[0] / 255.0f;
					nextM.at<float>(1, y, x) = (float)screenIn->currentAbsDifferenceLowRes.at<cv::Vec4b>(y, x)[1] / 255.0f;
					nextM.at<float>(2, y, x) = (float)screenIn->currentAbsDifferenceLowRes.at<cv::Vec4b>(y, x)[2] / 255.0f;
				}
			}
		}
	}

	void ScreenDifferenceArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}