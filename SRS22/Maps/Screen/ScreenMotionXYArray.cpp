#include "../../SRS22pch.h"
#include "ScreenMotionXYArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenInputIO.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"
#include "../../OpenCVHelpers.h"

namespace SRS22 {
	ScreenMotionXYArray::ScreenMotionXYArray(Brain* br) :
		ConceptArray(br, ArrayUidE::SCREENMOTION_MAP, "ScreenMotionXYArray", NeuronType::IS_INPUT,
			ScreenMotionXYArray_Width, 0.0f,
			"The XY location of the maximum frame to frame difference.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	ScreenMotionXYArray::~ScreenMotionXYArray() {
	}

	void ScreenMotionXYArray::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto screenIn = IOCommon::GetIO<ScreenInputIO>();
		if (screenIn->currentAbsDifferenceLowRes.empty() == false) {
			// 8UC4 : dims=2 rows=270 cols=640
			cv::Mat& d = screenIn->currentAbsDifferenceLowRes;
			float maxV = 0.0f;
			int maxX = 0;
			int maxY = 0;
			int w = d.cols;
			int h = d.rows;
			std::string ty = OpenCVHelpers::CVMatrixInfo(d);
			// Find pixel of greatest difference, thus greatest motion.
			for (int r = 0; r < h; r++) {
				for (int c = 0; c < w; c++) {
					// 8UC4 : dims=2 rows=270 cols=640
					const float s = (float)d.at<cv::Vec4b>(r, c)[0] + (float)d.at<cv::Vec4b>(r, c)[1] + (float)d.at<cv::Vec4b>(r, c)[2];
					if (s > maxV) {
						maxV = s;
						maxX = c;
						maxY = r;
					}
				}
			}
			nextM.at<float>(0, 0, 0) = (float)maxX / (float)w;
			nextM.at<float>(0, 0, 1) = (float)maxY / (float)h;
		}
	}

	void ScreenMotionXYArray::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}