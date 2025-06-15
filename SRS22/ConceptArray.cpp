#include "ConceptArray.h"
#include "Brain.h"
#include "Cortex.h"
#include <string>
#include <format>
#include "ArrayUIDs.h"
#include <opencv2/core/mat.hpp>
#include <opencv2/core/hal/interface.h>

namespace SRS22 {
	ConceptArray::ConceptArray(Brain* br, ArrayUidE UID, std::string ArrayName, NeuronType neuronType, int cols, float decayFactor, std::string ArrayDescription) :
		myBrain(br),
		ArrayName(ArrayName),
		neuronType(neuronType),
		UID(UID),
		cols(cols),
		rows(1),
		depth(1),
		totalSize(cols),
		decayFactor(decayFactor),
		ArrayDescription(ArrayDescription),
		rowsXcols(rows* cols) {
		dims[0] = depth;
		dims[1] = rows;
		dims[2] = cols;

	}

	ConceptArray::ConceptArray(Brain* br, ArrayUidE UID, std::string ArrayName, NeuronType neuronType, int rows, int cols, float decayFactor, std::string ArrayDescription) :
		myBrain(br),
		ArrayName(ArrayName),
		neuronType(neuronType),
		UID(UID),
		cols(cols),
		rows(rows),
		depth(1),
		totalSize(cols* rows),
		decayFactor(decayFactor),
		ArrayDescription(ArrayDescription),
		rowsXcols(rows* cols) {
		dims[0] = depth;
		dims[1] = rows;
		dims[2] = cols;
	}

	ConceptArray::ConceptArray(Brain* br, ArrayUidE UID, std::string ArrayName, NeuronType neuronType, int depth, int rows, int cols, float decayFactor, std::string ArrayDescription) :
		myBrain(br),
		ArrayName(ArrayName),
		neuronType(neuronType),
		UID(UID),
		cols(cols),
		rows(rows),
		depth(depth),
		totalSize(cols* rows* depth),
		decayFactor(decayFactor),
		ArrayDescription(ArrayDescription),
		rowsXcols(rows* cols) {
		dims[0] = depth;
		dims[1] = rows;
		dims[2] = cols;
	}

	ConceptArray::~ConceptArray() {
	}

	void ConceptArray::setupCVMatMirrors() {
		M = cv::Mat(3, dims, CV_32F, myBrain->cortex->neurons.getCurrentPointer(cortexStartIndex));
		nextM = cv::Mat(3, dims, CV_32F, myBrain->cortex->neurons.getNextPointer(cortexStartIndex));
	}

	void ConceptArray::PostCreate(Brain& b) {
		Cortex& c = *b.cortex;
		for (int i = cortexStartIndex; i < cortexStartIndex + totalSize; i++) {
			c.neurons.state[i] = neuronType;
		}
	}

	void ConceptArray::CopyToNext() {
		memcpy_s(myBrain->cortex->neurons.getNextPointer(cortexStartIndex), totalSize * sizeof(float), myBrain->cortex->neurons.getCurrentPointer(cortexStartIndex), totalSize * sizeof(float));
	}

	void ConceptArray::ComputeNextState(boolean doParallel) {
	}

	/// <summary>
	/// The cortex does the copy of nextState to state.
	/// Does nothing.
	/// </summary>
	void ConceptArray::LatchNewState(boolean doParallel) {
		// The cortex does the copy of nextState to state.
		// Nothing to do here.
	}

	void ConceptArray::put(int idx, float val) { myBrain->put(idx + cortexStartIndex, val); }
	float ConceptArray::get(int idx) { return myBrain->get(idx + cortexStartIndex); }
	void ConceptArray::put(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, val); }
	float ConceptArray::get(int row, int col) { return myBrain->get(row * cols + col + cortexStartIndex); }
	void ConceptArray::put(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, val); }
	float ConceptArray::get(int depth, int row, int col) { return myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex); }

	void ConceptArray::putNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, val); }
	float ConceptArray::getNext(int idx) { return myBrain->getNext(idx + cortexStartIndex); }
	void ConceptArray::putNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, val); }
	float ConceptArray::getNext(int row, int col) { return myBrain->getNext(row * cols + col + cortexStartIndex); }
	void ConceptArray::putNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, val); }
	float ConceptArray::getNext(int depth, int row, int col) { return myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex); }

	void ConceptArray::add(int idx, float val) { myBrain->put(idx + cortexStartIndex, myBrain->get(idx + cortexStartIndex) + val); }
	void ConceptArray::add(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, myBrain->get(row * cols + col + cortexStartIndex) + val); }
	void ConceptArray::add(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex) + val); }

	void ConceptArray::addNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, myBrain->getNext(idx + cortexStartIndex) + val); }
	void ConceptArray::addNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, myBrain->getNext(row * cols + col + cortexStartIndex) + val); }
	void ConceptArray::addNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex) + val); }

	void ConceptArray::sub(int idx, float val) { myBrain->put(idx + cortexStartIndex, myBrain->get(idx + cortexStartIndex) - val); }
	void ConceptArray::sub(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, myBrain->get(row * cols + col + cortexStartIndex) - val); }
	void ConceptArray::sub(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex) - val); }

	void ConceptArray::subNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, myBrain->getNext(idx + cortexStartIndex) - val); }
	void ConceptArray::subNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, myBrain->getNext(row * cols + col + cortexStartIndex) - val); }
	void ConceptArray::subNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex) - val); }

	void ConceptArray::mul(int idx, float val) { myBrain->put(idx + cortexStartIndex, myBrain->get(idx + cortexStartIndex) * val); }
	void ConceptArray::mul(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, myBrain->get(row * cols + col + cortexStartIndex) * val); }
	void ConceptArray::mul(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex) * val); }

	void ConceptArray::mulNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, myBrain->getNext(idx + cortexStartIndex) * val); }
	void ConceptArray::mulNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, myBrain->getNext(row * cols + col + cortexStartIndex) * val); }
	void ConceptArray::mulNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex) * val); }

	void ConceptArray::div(int idx, float val) { myBrain->put(idx + cortexStartIndex, myBrain->get(idx + cortexStartIndex) / val); }
	void ConceptArray::div(int row, int col, float val) { myBrain->put(row * cols + col + cortexStartIndex, myBrain->get(row * cols + col + cortexStartIndex) / val); }
	void ConceptArray::div(int depth, int row, int col, float val) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex) / val); }

	void ConceptArray::divNext(int idx, float val) { myBrain->putNext(idx + cortexStartIndex, myBrain->getNext(idx + cortexStartIndex) / val); }
	void ConceptArray::divNext(int row, int col, float val) { myBrain->putNext(row * cols + col + cortexStartIndex, myBrain->getNext(row * cols + col + cortexStartIndex) / val); }
	void ConceptArray::divNext(int depth, int row, int col, float val) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex) / val); }

	void ConceptArray::clampp(int idx, float min, float max) { myBrain->put(idx + cortexStartIndex, std::clamp(myBrain->get(idx + cortexStartIndex), min, max)); }
	void ConceptArray::clampp(int row, int col, float min, float max) { myBrain->put(row * cols + col + cortexStartIndex, std::clamp(myBrain->get(row * cols + col + cortexStartIndex), min, max)); }
	void ConceptArray::clampp(int depth, int row, int col, float min, float max) { myBrain->put(depth * rowsXcols + row * cols + col + cortexStartIndex, std::clamp(myBrain->get(depth * rowsXcols + row * cols + col + cortexStartIndex), min, max)); }

	void ConceptArray::clampNext(int idx, float min, float max) { myBrain->putNext(idx + cortexStartIndex, std::clamp(myBrain->getNext(idx + cortexStartIndex), min, max)); }
	void ConceptArray::clampNext(int row, int col, float min, float max) { myBrain->putNext(row * cols + col + cortexStartIndex, std::clamp(myBrain->getNext(row * cols + col + cortexStartIndex), min, max)); }
	void ConceptArray::clampNext(int depth, int row, int col, float min, float max) { myBrain->putNext(depth * rowsXcols + row * cols + col + cortexStartIndex, std::clamp(myBrain->getNext(depth * rowsXcols + row * cols + col + cortexStartIndex), min, max)); }

	bool ConceptArray::FindMaxValue(const float minV, OUT int& col, OUT int& row, OUT int& depth, OUT float& v) {
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

	std::string ConceptArray::Debug() {
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