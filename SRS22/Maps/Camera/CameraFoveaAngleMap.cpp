#include "../../pch.h"
#include "CameraFoveaMap.h"
#include "CameraFoveaAngleMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraFoveaAngleMap::CameraFoveaAngleMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE_MAP, false, "CameraFoveaAngleMap",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles.") {
	}

	CameraFoveaAngleMap::~CameraFoveaAngleMap() {
	}

	void CameraFoveaAngleMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		ConceptMap* foveaMap = myBrain->FindMap(MapUidE::CAMERAFOVEA_MAP).value().get();
		cv::Mat fovea = foveaMap->M.charges;

		int w = foveaMap->Width();
		int h = foveaMap->Height();
		assert(foveaMap->Depth() == 3);
		// For each pixel do a vote on angle and x,y position much like Hough circle.
		for (int y = 0; y < h; y++) {
			for (int x = 0; x < w; x++) {
				
			}
		}
	}

	void CameraFoveaAngleMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}