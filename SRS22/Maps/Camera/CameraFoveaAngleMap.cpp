#include "../../pch.h"
#include "CameraFoveaMap.h"
#include "CameraFoveaAngleMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../HardwareIO/CameraAttnSpotIO.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraFoveaAngleMap000::CameraFoveaAngleMap000(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE000_MAP, false, "CameraFoveaAngleMap000",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 0 deg.") {
	}

	CameraFoveaAngleMap000::~CameraFoveaAngleMap000() {
	}

	void CameraFoveaAngleMap000::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles000.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap000::LatchNewState() {
		ConceptMap::LatchNewState();
	}

	CameraFoveaAngleMap225::CameraFoveaAngleMap225(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE225_MAP, false, "CameraFoveaAngleMap225",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 22.5 deg.") {
	}

	CameraFoveaAngleMap225::~CameraFoveaAngleMap225() {
	}

	void CameraFoveaAngleMap225::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles225.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap225::LatchNewState() {
		ConceptMap::LatchNewState();
	}

	CameraFoveaAngleMap450::CameraFoveaAngleMap450(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE450_MAP, false, "CameraFoveaAngleMap450",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 45 deg.") {
	}

	CameraFoveaAngleMap450::~CameraFoveaAngleMap450() {
	}

	void CameraFoveaAngleMap450::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles450.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap450::LatchNewState() {
		ConceptMap::LatchNewState();
	}

	CameraFoveaAngleMap675::CameraFoveaAngleMap675(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE675_MAP, false, "CameraFoveaAngleMap675",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 67.5 deg.") {
	}

	CameraFoveaAngleMap675::~CameraFoveaAngleMap675() {
	}

	void CameraFoveaAngleMap675::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles675.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap675::LatchNewState() {
		ConceptMap::LatchNewState();
	}

	CameraFoveaAngleMap900::CameraFoveaAngleMap900(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE900_MAP, false, "CameraFoveaAngleMap900",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 90 deg.") {
	}

	CameraFoveaAngleMap900::~CameraFoveaAngleMap900() {
	}

	void CameraFoveaAngleMap900::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles900.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap900::LatchNewState() {
		ConceptMap::LatchNewState();
	}

	CameraFoveaAngleMap1125::CameraFoveaAngleMap1125(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE1125_MAP, false, "CameraFoveaAngleMap1125",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 112.5 deg.") {
	}

	CameraFoveaAngleMap1125::~CameraFoveaAngleMap1125() {
	}

	void CameraFoveaAngleMap1125::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1125.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap1125::LatchNewState() {
		ConceptMap::LatchNewState();
	}

	CameraFoveaAngleMap1350::CameraFoveaAngleMap1350(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE1350_MAP, false, "CameraFoveaAngleMap1350",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 135 deg.") {
	}

	CameraFoveaAngleMap1350::~CameraFoveaAngleMap1350() {
	}

	void CameraFoveaAngleMap1350::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1350.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap1350::LatchNewState() {
		ConceptMap::LatchNewState();
	}

	CameraFoveaAngleMap1575::CameraFoveaAngleMap1575(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE1575_MAP, false, "CameraFoveaAngleMap1575",
			cv::Vec3f(0.0, 0.0, 0.0),
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 157.5 deg.") {
	}

	CameraFoveaAngleMap1575::~CameraFoveaAngleMap1575() {
	}

	void CameraFoveaAngleMap1575::ComputeNextState() {
		ConceptMap::ComputeNextState();

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1575.copyTo(nextM.charges);
	}

	void CameraFoveaAngleMap1575::LatchNewState() {
		ConceptMap::LatchNewState();
	}
}