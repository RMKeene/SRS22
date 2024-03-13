#include "ConceptMap.h"
#include "Brain.h"
#include "Cortex.h"
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
		dims[0] = depth;
		dims[1] = rows;
		dims[2] = cols;

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
		dims[0] = depth;
		dims[1] = rows;
		dims[2] = cols;
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
		dims[0] = depth;
		dims[1] = rows;
		dims[2] = cols;
	}

	ConceptMap::~ConceptMap() {
	}

	void ConceptMap::setupCVMatMirrors() {
		M = cv::Mat(3, dims, CV_32FC1, &myBrain->cortex->neuronCharges[cortexStartIndex]);
		nextM = cv::Mat(3, dims, CV_32FC1, &myBrain->cortex->neuronChargesNext[cortexStartIndex]);
	}

	void ConceptMap::PostCreate(Brain& b) {

	}

	void ConceptMap::ComputeNextState() {
	}

	/// <summary>
	/// The cortex does the copy of nextState to state.
	/// This base implementation decays the nextM toward zero charge.
	/// Not multithreaded.
	/// </summary>
	void ConceptMap::LatchNewState() {
		//for (int i = cortexStartIndex; i < cortexStartIndex + totalSize; i++) {
		//	myBrain->cortex->neuronChargesNext[i] = myBrain->cortex->neuronChargesNext[i] * decayFactor;
		//}
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

	void ConceptMap::clampp(int idx, float min, float max) { myBrain->put(idx + cortexStartIndex, std::clamp(myBrain->get(idx + cortexStartIndex), min, max)); }
	void ConceptMap::clampp(int row, int col, float min, float max) { myBrain->put(row * cols + col + cortexStartIndex, std::clamp(myBrain->get(row * cols + col + cortexStartIndex), min, max)); }
	void ConceptMap::clampp(int depth, int row, int col, float min, float max) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, std::clamp(myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex), min, max)); }

	void ConceptMap::clampNext(int idx, float min, float max) { myBrain->putNext(idx + cortexStartIndex, std::clamp(myBrain->getNext(idx + cortexStartIndex), min, max)); }
	void ConceptMap::clampNext(int row, int col, float min, float max) { myBrain->putNext(row * cols + col + cortexStartIndex, std::clamp(myBrain->getNext(row * cols + col + cortexStartIndex), min, max)); }
	void ConceptMap::clampNext(int depth, int row, int col, float min, float max) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, std::clamp(myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex), min, max)); }

	bool ConceptMap::FindMaxValue(const float minV, OUT int& col, OUT int& row, OUT int& depth, OUT float& v) {
		bool hit = false;
		// This translates to -FLT_MAX which is what we want.
		v = std::numeric_limits<float>::lowest();
		if (M.size.dims() == 1) {
			row = 0;
			depth = 0;
			for (int c = 0; c < M.size[0]; c++) {
				const float f = M.at<float>(c);
				if (f > v) {
					v = f;
					col = c;
					hit |= f > minV;
				}
			}
		}
		else if (M.size.dims() == 2) {
			depth = 0;
			for (int r = 0; r < M.size[0]; r++) {
				for (int c = 0; c < M.size[1]; c++) {
					const float f = M.at<float>(r, c);
					if (f > v) {
						v = f;
						col = c;
						row = r;
						hit |= f > minV;
					}
				}
			}
		}
		else { // Dim count is 3
			depth = 0;
			for (int d = 0; d < M.size[0]; d++) {
				for (int r = 0; r < M.size[1]; r++) {
					for (int c = 0; c < M.size[2]; c++) {
						const float f = M.at<float>(d, r, c);
						if (f > v) {
							v = f;
							col = c;
							row = r;
							depth = d;
							hit |= f > minV;

						}
					}
				}
			}
		}
		return hit;
	}

	std::string ConceptMap::Debug() {
		std::stringstream s;
		s << "M.dims = " << M.dims;
		s << " entriesCount=" << totalSize;
		s << " M.charges.dims = [";
		for (int i = 0; i < M.dims; ++i) {
			if (i) s << " X ";
			s << M.size[i];
		}
		s << "] temp.channels = " << M.channels() << std::endl;

		return s.str();
	}

}