#include "../../pch.h"
#include "ScreenMotionXYMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/ScreenInputIO.h"
#include "../../HardwareIO/ScreenAttnSpotIO.h"
#include "../../OpenCVHelpers.h"

namespace SRS22 {
	ScreenMotionXYMap::ScreenMotionXYMap(Brain* br) :
		ConceptMap(br, MapUidE::SCREENMOTION_MAP, true, "ScreenMotionXYMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			ScreenMotionXYMap_Width,
			"The XY location of the maximum frame to frame difference.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
		SetDecayFactors(0.0f);
	}

	ScreenMotionXYMap::~ScreenMotionXYMap() {
	}

	void ScreenMotionXYMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

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
			nextM.charges.at<float>(0) += (float)maxX / (float)w;
			nextM.charges.at<float>(1) += (float)maxY / (float)h;
		}
	}

	void ScreenMotionXYMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}