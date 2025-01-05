#include "../../SRS22pch.h"
#include "CameraFoveaAngleMap.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraFoveaAngleMap000::CameraFoveaAngleMap000(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE000_MAP, "CameraFoveaAngleMap000", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 0 deg.") {
	}

	CameraFoveaAngleMap000::~CameraFoveaAngleMap000() {
	}

	void CameraFoveaAngleMap000::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles000.copyTo(nextM);
	}

	void CameraFoveaAngleMap000::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}

	CameraFoveaAngleMap225::CameraFoveaAngleMap225(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE225_MAP, "CameraFoveaAngleMap225", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 22.5 deg.") {
	}

	CameraFoveaAngleMap225::~CameraFoveaAngleMap225() {
	}

	void CameraFoveaAngleMap225::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles225.copyTo(nextM);
	}

	void CameraFoveaAngleMap225::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}

	CameraFoveaAngleMap450::CameraFoveaAngleMap450(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE450_MAP, "CameraFoveaAngleMap450", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 45 deg.") {
	}

	CameraFoveaAngleMap450::~CameraFoveaAngleMap450() {
	}

	void CameraFoveaAngleMap450::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles450.copyTo(nextM);
	}

	void CameraFoveaAngleMap450::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}

	CameraFoveaAngleMap675::CameraFoveaAngleMap675(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE675_MAP, "CameraFoveaAngleMap675", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 67.5 deg.") {
	}

	CameraFoveaAngleMap675::~CameraFoveaAngleMap675() {
	}

	void CameraFoveaAngleMap675::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles675.copyTo(nextM);
	}

	void CameraFoveaAngleMap675::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}

	CameraFoveaAngleMap900::CameraFoveaAngleMap900(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE900_MAP, "CameraFoveaAngleMap900", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 90 deg.") {
	}

	CameraFoveaAngleMap900::~CameraFoveaAngleMap900() {
	}

	void CameraFoveaAngleMap900::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles900.copyTo(nextM);
	}

	void CameraFoveaAngleMap900::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}

	CameraFoveaAngleMap1125::CameraFoveaAngleMap1125(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE1125_MAP, "CameraFoveaAngleMap1125", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 112.5 deg.") {
	}

	CameraFoveaAngleMap1125::~CameraFoveaAngleMap1125() {
	}

	void CameraFoveaAngleMap1125::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1125.copyTo(nextM);
	}

	void CameraFoveaAngleMap1125::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}

	CameraFoveaAngleMap1350::CameraFoveaAngleMap1350(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE1350_MAP, "CameraFoveaAngleMap1350", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 135 deg.") {
	}

	CameraFoveaAngleMap1350::~CameraFoveaAngleMap1350() {
	}

	void CameraFoveaAngleMap1350::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1350.copyTo(nextM);
	}

	void CameraFoveaAngleMap1350::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}

	CameraFoveaAngleMap1575::CameraFoveaAngleMap1575(Brain* br) :
		ConceptMap(br, MapUidE::CAMERAFOVEAANGLE1575_MAP, "CameraFoveaAngleMap1575", true,
			3, CameraFoveaMap_Height, CameraFoveaMap_Width, 0.0f,
			"Camera fovea center edge angles. 157.5 deg.") {
	}

	CameraFoveaAngleMap1575::~CameraFoveaAngleMap1575() {
	}

	void CameraFoveaAngleMap1575::ComputeNextState(boolean doParallel) {
		ConceptMap::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1575.copyTo(nextM);
	}

	void CameraFoveaAngleMap1575::LatchNewState(boolean doParallel) {
		ConceptMap::LatchNewState(doParallel);
	}
}