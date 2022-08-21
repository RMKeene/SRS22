#include "../pch.h"
#include "CameraMotionXYMap.h"
#include "../HardwareIO/IOCommon.h"
#include "../HardwareIO/CameraInIO.h"
#include "../HardwareIO/CameraAttnSpotIO.h"
#include "../OpenCVHelpers.h"

namespace SRS22 {

	CameraMotionXYMap::CameraMotionXYMap(Brain* br) :
		SRSUnit(br, "CameraMotionXYMap",
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
			cv::Vec3f(0.0, 0.0, 0.0),
			CameraMotionXYMap_Width,
			"The XY location of the maximum frame to frame difference.") {
		displayMode = SRSUnitDisplayModes::TWOVALUECAMERA;
	}

	CameraMotionXYMap::~CameraMotionXYMap() {

	}

	void CameraMotionXYMap::ComputeNextState() {
		SRSUnit::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		if (cameraIn->currentAbsDifferenceLowRes.empty() == false) {
			cv::Mat& d = cameraIn->currentAbsDifferenceLowRes;
			float maxV = 0.0f;
			int maxX = 0;
			int maxY = 0;
			int w = d.size[2];
			int h = d.size[1];
			std::string ty = OpenCVHelpers::CVMatrixInfo(d);
			for (int r = 0; r < h; r++) {
				for (int c = 0; c < w; c++) {
					// 32FC1
					// std::string ty = OpenCVHelpers::CVTypeToStr(d.type());
					const float s = d.at<float>(0, r, c) + d.at<float>(1, r, c) + d.at<float>(2, r, c);
					if (s > maxV) {
						maxV = s;
						maxX = c;
						maxY = r;
					}
				}
			}
			nextM.charges.at<float>(0) = (float)maxX / (float)w;
			nextM.charges.at<float>(1) = (float)maxY / (float)h;
		}
	}

	void CameraMotionXYMap::LatchNewState() {
		SRSUnit::LatchNewState();
	}

}
