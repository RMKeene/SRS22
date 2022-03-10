#include "pch.h"
#include "Brain.h"
#include "SRSUnit.h"
#include "FastRand.h"

namespace SRS22 {
	using namespace std;

	void Brain::Tick() {

	}

	pair<bool, string> Brain::Load(string fileName) {

		return pair<bool, string>(false, "Not yet implemented");
	}

	bool Brain::Store(string fileName) {
		return false;
	}

	std::optional<PatternConnection> Brain::GetRandomNeuron(
		shared_ptr<SRSUnit> origin) {

		for (int i = 0; i < 2; i++) {
			float r = static_cast <float> (xorshf96()) / static_cast <float> (RAND_MAX);
			if (r < origin->ctrip.A) { // Select random neuron from self
				if (origin->size() > 0) {
					PatternConnection c(origin, xorshf96() % origin->size());
					return std::optional<PatternConnection>{ c };
				}
			}
			else if (r < origin->ctrip.B) { // Select from near concepts
				if (origin->nearMaps.size() > 0) {
					shared_ptr<SRSUnit> other = origin->nearMaps[xorshf96() % origin->nearMaps.size()];
					if (other->size() > 0) {
						PatternConnection c(origin, xorshf96() % other->size());
						return std::optional<PatternConnection>{ c };
					}
				}
			}
			else { // Select from far concepts
				if (origin->farMaps.size()) {
					shared_ptr<SRSUnit> other = origin->farMaps[xorshf96() % origin->farMaps.size()];
					if (other->size() > 0) {
						PatternConnection c(origin, xorshf96() % other->size());
						return std::optional<PatternConnection>{ c };
					}
				}
			}
		}

		return std::nullopt;
	}

	void Brain::Init() {

	}

	void Brain::Shutdown() {

	}

	void Brain::UnitTest() {
		int w = screenInput.GetScreenWidth();
		int h = screenInput.GetScreenHeight();
		printf("Screen %d x %d\n", w, h);
	}

	void Brain::PostCreateAllSRSUnits() {
		for (auto u : conceptMaps)
			u->PostCreate(*this);
	}
}