#include "../../SRS22pch.h"
#include "CameraFoveaAngleArray.h"
#include "../../HardwareIO/IOCommon.h"
#include "../../HardwareIO/CameraInIO.h"
#include "../../Brain.h"

namespace SRS22 {
	CameraFoveaAngleArray000::CameraFoveaAngleArray000(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAANGLE000_MAP, "CameraFoveaAngleArray000", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera fovea center edge angles. 0 deg.") {
	}

	CameraFoveaAngleArray000::~CameraFoveaAngleArray000() {
	}

	void CameraFoveaAngleArray000::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles000.copyTo(nextM);
	}

	void CameraFoveaAngleArray000::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}

	CameraFoveaAngleArray225::CameraFoveaAngleArray225(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAANGLE225_MAP, "CameraFoveaAngleArray225", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera fovea center edge angles. 22.5 deg.") {
	}

	CameraFoveaAngleArray225::~CameraFoveaAngleArray225() {
	}

	void CameraFoveaAngleArray225::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles225.copyTo(nextM);
	}

	void CameraFoveaAngleArray225::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}

	CameraFoveaAngleArray450::CameraFoveaAngleArray450(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAANGLE450_MAP, "CameraFoveaAngleArray450", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera fovea center edge angles. 45 deg.") {
	}

	CameraFoveaAngleArray450::~CameraFoveaAngleArray450() {
	}

	void CameraFoveaAngleArray450::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles450.copyTo(nextM);
	}

	void CameraFoveaAngleArray450::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}

	CameraFoveaAngleArray675::CameraFoveaAngleArray675(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAANGLE675_MAP, "CameraFoveaAngleArray675", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera fovea center edge angles. 67.5 deg.") {
	}

	CameraFoveaAngleArray675::~CameraFoveaAngleArray675() {
	}

	void CameraFoveaAngleArray675::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles675.copyTo(nextM);
	}

	void CameraFoveaAngleArray675::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}

	CameraFoveaAngleArray900::CameraFoveaAngleArray900(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAANGLE900_MAP, "CameraFoveaAngleArray900", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera fovea center edge angles. 90 deg.") {
	}

	CameraFoveaAngleArray900::~CameraFoveaAngleArray900() {
	}

	void CameraFoveaAngleArray900::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles900.copyTo(nextM);
	}

	void CameraFoveaAngleArray900::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}

	CameraFoveaAngleArray1125::CameraFoveaAngleArray1125(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAANGLE1125_MAP, "CameraFoveaAngleArray1125", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera fovea center edge angles. 112.5 deg.") {
	}

	CameraFoveaAngleArray1125::~CameraFoveaAngleArray1125() {
	}

	void CameraFoveaAngleArray1125::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1125.copyTo(nextM);
	}

	void CameraFoveaAngleArray1125::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}

	CameraFoveaAngleArray1350::CameraFoveaAngleArray1350(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAANGLE1350_MAP, "CameraFoveaAngleArray1350", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera fovea center edge angles. 135 deg.") {
	}

	CameraFoveaAngleArray1350::~CameraFoveaAngleArray1350() {
	}

	void CameraFoveaAngleArray1350::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1350.copyTo(nextM);
	}

	void CameraFoveaAngleArray1350::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}

	CameraFoveaAngleArray1575::CameraFoveaAngleArray1575(Brain* br) :
		ConceptArray(br, ArrayUidE::CAMERAFOVEAANGLE1575_MAP, "CameraFoveaAngleArray1575", NeuronType::IS_INPUT,
			3, CameraFoveaArray_Height, CameraFoveaArray_Width, 0.0f,
			"Camera fovea center edge angles. 157.5 deg.") {
	}

	CameraFoveaAngleArray1575::~CameraFoveaAngleArray1575() {
	}

	void CameraFoveaAngleArray1575::ComputeNextState(boolean doParallel) {
		ConceptArray::ComputeNextState(doParallel);

		auto cameraIn = IOCommon::GetIO<CameraInIO>();
		cameraIn->foveaAngles1575.copyTo(nextM);
	}

	void CameraFoveaAngleArray1575::LatchNewState(boolean doParallel) {
		ConceptArray::LatchNewState(doParallel);
	}
}