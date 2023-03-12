#include "pch.h"
#include "ConceptState.h"

namespace SRS22 {
	ConceptState::ConceptState(int cols) {
		charges.create(1, cols, CV_32FC1);
		cv::randu(charges, 0.0f, 1.0f);
	}

	ConceptState::ConceptState(int rows, int cols) {
		charges.create(rows, cols, CV_32FC1);
		cv::randu(charges, 0.0f, 1.0f);
	}

	ConceptState::ConceptState(int layers, int rows, int cols) {
		int out[3];
		out[0] = layers;
		out[1] = rows;
		out[2] = cols;
		charges.create(3, out, CV_32FC1);
		cv::randu(charges, 0.0f, 1.0f);
	}

	ConceptState::~ConceptState() {
	}

	float ConceptState::get(int col) {
		return charges.at<float>(col);
	}

	float ConceptState::get(int row, int col) {
		return charges.at<float>(row, col);
	}

	float ConceptState::get(int layer, int row, int col) {
		return charges.at<float>(layer, row, col);
	}

	void ConceptState::put(float v, int col) {
		charges.at<float>(col) = v;
	}

	void ConceptState::put(float v, int row, int col) {
		charges.at<float>(row, col) = v;
	}

	void ConceptState::put(float v, int layer, int row, int col) {
		charges.at<float>(layer, row, col) = v;
	}

	const cv::MatSize ConceptState::matSize() {
		return charges.size;
	}

	const int ConceptState::dimensionCount() {
		return charges.size.dims();
	}

	const int ConceptState::entriesCount() {
		return charges.total();
	}

	const int ConceptState::byteCount() {
		return charges.total() * charges.elemSize();
	}

	float ConceptState::Compare(std::shared_ptr<ConceptState> other, const int skip) {
		if (charges.size() != other->charges.size())
			throw std::logic_error("Missmatched ConseptState sizes: Compare");
		cv::Mat dst;
		cv::bitwise_xor(this->charges, other->charges, dst);
		return cv::countNonZero(dst) == 0;
	}

	void ConceptState::Copy(ConceptState& fromM, ConceptState& toM) {
		//if (fromM.charges.size().area() != toM.charges.size().area())
		//	throw std::logic_error("Missmatched ConseptState sizes: Copy");
		fromM.charges.copyTo(toM.charges);
	}

	bool ConceptState::FindMaxValue(const float minV, OUT int& col, OUT int& row, OUT int& depth, OUT float& v) {
		bool hit = false;
		// This translates to -FLT_MAX which is what we want.
		v = std::numeric_limits<float>::lowest();
		if (dimensionCount() == 1) {
			row = 0;
			depth = 0;
			for (int c = 0; c < charges.size[0]; c++) {
				const float f = charges.at<float>(c);
				if (f > v) {
					v = f;
					col = c;
					hit |= f > minV;
				}
			}
		}
		else if (dimensionCount() == 2) {
			depth = 0;
			for (int r = 0; r < charges.size[0]; r++) {
				for (int c = 0; c < charges.size[1]; c++) {
					const float f = charges.at<float>(r, c);
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
			for (int d = 0; d < charges.size[0]; d++) {
				for (int r = 0; r < charges.size[1]; r++) {
					for (int c = 0; c < charges.size[2]; c++) {
						const float f = charges.at<float>(d, r, c);
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

	std::string ConceptState::Debug() {
		std::stringstream s;
		s << "M.charges.dims = " << charges.dims;
		s << " matSize=" << matSize();
		s << " entriesCount=" << entriesCount();
		s << " byteCount=" << byteCount();
		s << " M.charges.dims = [";
		for (int i = 0; i < charges.dims; ++i) {
			if (i) s << " X ";
			s << charges.size[i];
		}
		s << "] temp.channels = " << charges.channels() << std::endl;

		return s.str();
	}
}