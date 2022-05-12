#include "pch.h"
#include "Brain.h"
#include "SRSUnit.h"
#include "FastRand.h"
#include <tchar.h>
#include <ppl.h>

using namespace concurrency;

namespace SRS22 {
	using namespace std;

	Brain::Brain() {

	}

	Brain::~Brain() {

	}

	void Brain::Tick() {
		if (SingleStepCount == 0)
			return;
		if (SingleStepCount > 0)
			SingleStepCount--;
		PreTick();

		// Call all SRSUnit ProcessState in parallel
		parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::shared_ptr<SRSUnit> n) {
			n->ComputeNextState();
			});

		// Call all SRSUnit LatchNewState in parallel.
		parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::shared_ptr<SRSUnit> n) {
			n->LatchNewState();
			});

		PostTick();
	}

	void Brain::PreTick() {
		screenInput.PreTick();
		audioInput.PreTick();
		audioOut.PreTick();
		cameraInput.PreTick();
		textIn.PreTick();
		textOut.PreTick();
		whiteboardIn.PreTick();
		whiteboardOut.PreTick();
	}
	
	void Brain::PostTick() {
		screenInput.PostTick();
		audioInput.PostTick();
		audioOut.PostTick();
		cameraInput.PostTick();
		textIn.PostTick();
		textOut.PostTick();
		whiteboardIn.PostTick();
		whiteboardOut.PostTick();
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
		// Hardware I/O setups.
		screenInput.Init();
		audioInput.Init();
		audioOut.Init();
		cameraInput.Init();
		textIn.Init();
		textOut.Init();
		whiteboardIn.Init();
		whiteboardOut.Init();

		PostCreateAllSRSUnits();
	}

	void Brain::Shutdown() {
		screenInput.Shutdown();
		audioInput.Shutdown();
		audioOut.Shutdown();
		cameraInput.Shutdown();
		textIn.Shutdown();
		textOut.Shutdown();
		whiteboardIn.Shutdown();
		whiteboardOut.Shutdown();
	}

	void Brain::UnitTest() {
		screenInput.UnitTest();
		audioInput.UnitTest();
		audioOut.UnitTest();
		cameraInput.UnitTest();
		textIn.UnitTest();
		textOut.UnitTest();
		whiteboardIn.UnitTest();
		whiteboardOut.UnitTest();
	}

	void Brain::DoNStep(int n) {
		SingleStepCount = clamp(n, 1, 10000);
	}

	void Brain::DoSingleStep() {
		SingleStepCount = 1;
	}

	void Brain::Pause() {
		SingleStepCount = 0;
	}

	void Brain::Continue() {
		SingleStepCount = -1;
	}

	void Brain::PostCreateAllSRSUnits() {
		for (auto u : conceptMaps)
			u->PostCreate(*this);
	}

	void Brain::TakeScreenSnapshot() {
		screenInput.TakeScreenSnapshot();
		//screenInput.DumpCurrentScreenSnapshot(_T("test.bmp"));
	}
}