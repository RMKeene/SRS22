#include "pch.h"
#include "ConceptState.h"

namespace SRS22 {

	ConceptState::ConceptState(int _w) : w(_w), h(0), d(0), size(_w), bytesize(_w), dims(1), wh(_w * 0) {
		charges = std::make_shared<float>(size);
	}

	ConceptState::ConceptState(int _w, int _h) : w(_w), h(_h), d(0), size(_w* _h), bytesize(_w* _h), dims(2), wh(_w* _h) {
		charges = std::make_shared<float>(size);
	}

	ConceptState::ConceptState(int _w, int _h, int _d) : w(_w), h(_h), d(_d), size(_w* h* _d), bytesize(_w* _h* _d), dims(2), wh(_w* _h) {
		charges = std::make_shared<float>(size);
	}

	ConceptState::~ConceptState() {
		// Let it go. (Elsa singing)
		charges.reset();
	}

	float ConceptState::get(int x) {
		return charges.get()[x];
	}

	float ConceptState::get(int x, int y) {
		return charges.get()[y * w + x];
	}

	float ConceptState::get(int x, int y, int z) {
		return charges.get()[z * wh + y * w + x];
	}

	void ConceptState::put(float v, int x) {
		charges.get()[x] = v;
	}

	void ConceptState::put(float v, int x, int y) {
		charges.get()[y * w + x] = v;
	}

	void ConceptState::put(float v, int x, int y, int z) {
		charges.get()[z * wh + y * w + x] = v;
	}

	float ConceptState::Compare(std::shared_ptr<ConceptState> other, const int skip) {
		double sum = 0.0;

		for (int i = 0; i < size; i += skip) {
			const float dv = charges.get()[i] - other->charges.get()[i];
			if (dv >= 0.0f)
				sum += dv;
			else
				sum -= dv;
		}

		return (float)(sum / (double)size);
	}

	void ConceptState::Copy(ConceptState& fromM, ConceptState& toM) {
		if (fromM.size != toM.size) {
			throw std::runtime_error("copy size missmatch in ConceptState.");
		}
		const float* f = fromM.charges.get();
		float* t = toM.charges.get();
		for (int i = 0; i < fromM.size; i++) {
			t[i] = f[i];
		}
	}
}