#include "../../pch.h"
#include "CameraFoveaMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"

namespace SRS22 {
	CameraFoveaMap::CameraFoveaMap(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEA_MAP, "CameraFoveaMap",
			ConnectivityTriple(0.10f, 0.75f, 0.15f, 100),
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width,
			"Raw pixel map of center of camera fovea in color.") {
		SetDecayFactors(false);
	}

	CameraFoveaMap::~CameraFoveaMap() {
	}

	void CameraFoveaMap::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		auto fovea = IOCommon::GetIO<CameraAttnSpotIO>();
		Rect r(Width(), Height(), fovea->GetPt());
		cameraIn->GetSubRect(nextM.charges, r);
		//std::string ss = CVMatrixInfo(nextM.charges);
		//ss = CVMatrixInfo(cameraIn->currentScreen);
	}

	void CameraFoveaMap::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}