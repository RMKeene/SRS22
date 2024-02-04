#include "ConceptMap.h"
#include "Brain.h"
#include <string>
#include <format>
#include "MapUIDs.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/hal/interface.h>

namespace SRS22 {
	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, int cols, float decayFactor, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(UID),
		cols(cols),
		rows(1),
		depth(1),
		totalSize(cols),
		decayFactor(decayFactor),
		MapDescription(MapDescription),
		rowsXcols(rows* cols) {
		numDims[0] = depth;
		numDims[1] = rows;
		numDims[2] = cols;

	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, int rows, int cols, float decayFactor, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(UID),
		cols(cols),
		rows(rows),
		depth(1),
		totalSize(cols* rows),
		decayFactor(decayFactor),
		MapDescription(MapDescription),
		rowsXcols(rows* cols) {
		numDims[0] = depth;
		numDims[1] = rows;
		numDims[2] = cols;
	}

	ConceptMap::ConceptMap(Brain* br, MapUidE UID, std::string MapName, int depth, int rows, int cols, float decayFactor, std::string MapDescription) :
		myBrain(br),
		MapName(MapName),
		UID(UID),
		cols(cols),
		rows(rows),
		depth(depth),
		totalSize(cols* rows* depth),
		decayFactor(decayFactor),
		MapDescription(MapDescription),
		rowsXcols(rows* cols) {
		numDims[0] = depth;
		numDims[1] = rows;
		numDims[2] = cols;
	}

	ConceptMap::~ConceptMap() {
	}

	void ConceptMap::setupCVMatMirrors() {
		M = cv::Mat(3, numDims, CV_32FC1, &myBrain->cortex->neuronCharges[cortexStartIndex]);
		nextM = cv::Mat(3, numDims, CV_32FC1, &myBrain->cortex->neuronChargesNext[cortexStartIndex]);
	}

	void ConceptMap::PostCreate(Brain& b) {

	}

	void ConceptMap::ComputeNextState() {
	}

	/// <summary>
	/// Decay and then add nextM to M. The set nextM to zeros.
	/// </summary>
	void ConceptMap::LatchNewState() {
		// Cortex does the next state transfer of nextCharge to charge.
	}

	std::string ConceptMap::Debug() {
		return std::format("");
	}

	void ConceptMap::put(int idx, float val) { myBrain->put(idx + cortexStartIndex, val); }
	float ConceptMap::get(int idx) { return myBrain->get(idx + cortexStartIndex); }
	void ConceptMap::put(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, val); }
	float ConceptMap::get(int row, int col) { return myBrain->get(row * cols + col + cortexStartIndex); }
	void ConceptMap::put(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, val); }
	float ConceptMap::get(int depth, int row, int col) { return myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex); }

	void ConceptMap::putNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, val); }
	float ConceptMap::getNext(int idx) { return myBrain->getNext(idx + cortexStartIndex); }
	void ConceptMap::putNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, val); }
	float ConceptMap::getNext(int row, int col) { return myBrain->getNext(row * cols + col + cortexStartIndex); }
	void ConceptMap::putNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, val); }
	float ConceptMap::getNext(int depth, int row, int col) { return myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex); }

	void ConceptMap::add(int idx, float val) { myBrain->put(idx + cortexStartIndex, myBrain->get(idx + cortexStartIndex) + val); }
	void ConceptMap::add(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, myBrain->get(row * cols + col + cortexStartIndex) + val); }
	void ConceptMap::add(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex) + val); }

	void ConceptMap::addNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, myBrain->getNext(idx + cortexStartIndex) + val); }
	void ConceptMap::addNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, myBrain->getNext(row * cols + col + cortexStartIndex) + val); }
	void ConceptMap::addNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex) + val); }

	void ConceptMap::sub(int idx, float val) { myBrain->put(idx + cortexStartIndex, myBrain->get(idx + cortexStartIndex) - val); }
	void ConceptMap::sub(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, myBrain->get(row * cols + col + cortexStartIndex) - val); }
	void ConceptMap::sub(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex) - val); }

	void ConceptMap::subNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, myBrain->getNext(idx + cortexStartIndex) - val); }
	void ConceptMap::subNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, myBrain->getNext(row * cols + col + cortexStartIndex) - val); }
	void ConceptMap::subNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex) - val); }

	void ConceptMap::mul(int idx, float val) { myBrain->put(idx + cortexStartIndex, myBrain->get(idx + cortexStartIndex) * val); }
	void ConceptMap::mul(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, myBrain->get(row * cols + col + cortexStartIndex) * val); }
	void ConceptMap::mul(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex) * val); }

	void ConceptMap::mulNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, myBrain->getNext(idx + cortexStartIndex) * val); }
	void ConceptMap::mulNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, myBrain->getNext(row * cols + col + cortexStartIndex) * val); }
	void ConceptMap::mulNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex) * val); }

	void ConceptMap::div(int idx, float val) { myBrain->put(idx + cortexStartIndex, myBrain->get(idx + cortexStartIndex) / val); }
	void ConceptMap::div(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, myBrain->get(row * cols + col + cortexStartIndex) / val); }
	void ConceptMap::div(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex) / val); }

	void ConceptMap::divNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, myBrain->getNext(idx + cortexStartIndex) / val); }
	void ConceptMap::divNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, myBrain->getNext(row * cols + col + cortexStartIndex) / val); }
	void ConceptMap::divNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex) / val); }

	void ConceptMap::clampp(int idx, float min = -1.0f, float max = 1.0f) { myBrain->put(idx + cortexStartIndex, std::clamp(myBrain->get(idx + cortexStartIndex), min, max)); }
	void ConceptMap::clampp(int row, int col, float min = -1.0f, float max = 1.0f) { myBrain->put(row * cols + col + cortexStartIndex, std::clamp(myBrain->get(row * cols + col + cortexStartIndex), min, max)); }
	void ConceptMap::clampp(int depth, int row, int col, float min = -1.0f, float max = 1.0f) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, std::clamp(myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex), min, max)); }

	void ConceptMap::clampNext(int idx, float min = -1.0f, float max = 1.0f) { myBrain->putNext(idx + cortexStartIndex, std::clamp(myBrain->getNext(idx + cortexStartIndex), min, max)); }
	void ConceptMap::clampNext(int row, int col, float min = -1.0f, float max = 1.0f) { myBrain->putNext(row * cols + col + cortexStartIndex, std::clamp(myBrain->getNext(row * cols + col + cortexStartIndex), min, max)); }
	void ConceptMap::clampNext(int depth, int row, int col, float min = -1.0f, float max = 1.0f) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, std::clamp(myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex), min, max)); }


}