#include "pch.h"
#include "ConceptMap.h"
#include "ConnectivityTriple.h"
#include "Brain.h"
#include "BrainLocatable.h"

namespace SRS22 {
	ConceptMap::ConceptMap(Brain* br, MapUidE UID, bool isConnectable, std::string MapName, const cv::Vec3f location, int cols, std::string MapDescription) :
		BrainLocatable(location),
		myBrain(br),
		MapName(MapName),
		UID(UID),
		M(cols), 
		nextM(cols),
		MapDescription(MapDescription) {

		isConnectableFlag = isConnectable;
	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, bool isConnectable, std::string MapName, const cv::Vec3f location, int rows, int cols, std::string MapDescription) :
		BrainLocatable(location),
		myBrain(br),
		MapName(MapName),
		UID(UID),
		M(rows, cols), 
		nextM(rows, cols),
		MapDescription(MapDescription) {

		isConnectableFlag = isConnectable;
	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, bool isConnectable, std::string MapName, const cv::Vec3f location, int layers, int rows, int cols, std::string MapDescription) :
		BrainLocatable(location),
		myBrain(br),
		MapName(MapName),
		UID(UID),
		M(layers, rows, cols), 
		nextM(layers, rows, cols),
		MapDescription(MapDescription) {

		isConnectableFlag = isConnectable;
	}

	ConceptMap::~ConceptMap() {
	}

	const cv::MatSize ConceptMap::matSize() {
		return M.matSize();
	}

	const int ConceptMap::entriesCount() {
		return M.entriesCount();
	}

	const int ConceptMap::byteCount() {
		return M.byteCount();
	}

	void ConceptMap::PostCreate(Brain& b) {

	}

	void ConceptMap::ComputeNextState() {

	}

	/// <summary>
	/// Decay and then add nextM to M. The set nextM to zeros.
	/// </summary>
	void ConceptMap::LatchNewState() {
		M.charges = M.charges * decayFactor + nextM.charges;
		nextM.charges = 0.0f;
	}

	std::string ConceptMap::Debug() {
		std::string ret = M.Debug();
		return ret;
	}

	int ConceptMap::GetRandomLinearOffset() {
		return M.entriesCount();
	}

	float ConceptMap::GetChargeValue(const int linearOffset) {
		return *(((float*)M.charges.data) + linearOffset);
	}

	void ConceptMap::SetChargeValue(const int linearOffset, const float c) {
		*(((float*)M.charges.data) + linearOffset) = c;
	}

	void ConceptMap::AddToChargeValue(const int linearOffset, const float c) {
		float* p = (((float*)M.charges.data) + linearOffset);
		*p = *p + c;
	}

}