#include "pch.h"
#include "Brain.h"
#include "SRSUnit.h"
#include "FastRand.h"
#include <tchar.h>
#include <ppl.h>
#include "Maps/ScreenFoveaMap.h"
#include "Maps/ScreenAttnSpotMap.h"
#include "Maps/ScreenDifferenceMap.h"
#include "Maps/ScreenMotionXYMap.h"
#include "Maps/RandomMap.h"
#include "Maps/CameraFoveaMap.h"
#include "Maps/CameraAttnSpotMap.h"
#include "Maps/CameraDifferenceMap.h"
#include "Maps/CameraMotionXYMap.h"

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
		parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::pair<std::string, std::shared_ptr<SRSUnit>> n) {
			n.second->ComputeNextState();
			});

		// Call all SRSUnit LatchNewState in parallel.
		parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::pair<std::string, std::shared_ptr<SRSUnit>> n) {
			n.second->LatchNewState();
			});

		PostTick();

		tickCount++;
	}

	void Brain::PreTick() {
		screenInput.PreTick();
		screenFovea.PreTick();
		audioInput.PreTick();
		audioOut.PreTick();
		cameraInput.PreTick();
		cameraFovea.PreTick();
		textIn.PreTick();
		textOut.PreTick();
		whiteboardIn.PreTick();
		whiteboardOut.PreTick();
	}
	
	void Brain::PostTick() {
		screenFovea.PostTick();
		screenInput.PostTick();
		audioInput.PostTick();
		audioOut.PostTick();
		cameraFovea.PostTick();
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
			if (r < origin->ctrip.selfFract) { // Select random neuron from self
				if (origin->entriesCount() > 0) {
					PatternConnection c(origin, xorshf96() % origin->entriesCount());
					return std::optional<PatternConnection>{ c };
				}
			}
			else if (r < origin->ctrip.nearbyFract) { // Select from near concepts
				if (origin->nearMaps.size() > 0) {
					shared_ptr<SRSUnit> other = origin->nearMaps[xorshf96() % origin->nearMaps.size()];
					if (other->entriesCount() > 0) {
						PatternConnection c(origin, xorshf96() % other->entriesCount());
						return std::optional<PatternConnection>{ c };
					}
				}
			}
			else { // Select from far concepts
				if (origin->farMaps.size()) {
					shared_ptr<SRSUnit> other = origin->farMaps[xorshf96() % origin->farMaps.size()];
					if (other->entriesCount() > 0) {
						PatternConnection c(origin, xorshf96() % other->entriesCount());
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

		// Virtual hardware devices.
		screenFovea.Init(Point(screenInput.GetScreenWidth() / 2, screenInput.GetScreenHeight() / 2),
			127, 127, screenInput.GetScreenRect());
		cameraFovea.Init(Point(cameraInput.GetCameraWidth() / 2, cameraInput.GetCameraHeight() / 2),
			64, 64, cameraInput.GetCameraRect());

		// All Map instances. Keep in alphabetical order please.
		AddMap(make_shared<CameraAttnSpotMap>(this));
		AddMap(make_shared<CameraDifferenceMap>(this));
		AddMap(make_shared<CameraFoveaMap>(this));
		AddMap(make_shared<CameraMotionXYMap>(this));
		AddMap(make_shared<RandomMap>(this));
		AddMap(make_shared<ScreenAttnSpotMap>(this));
		AddMap(make_shared<ScreenDifferenceMap>(this));
		AddMap(make_shared<ScreenFoveaMap>(this));
		AddMap(make_shared<ScreenMotionXYMap>(this));

		// Anonymouse Maps

		// Compile the SRS system relationships.
		PostCreateAllSRSUnits();
	}

	void Brain::Shutdown() {
		screenFovea.Shutdown();
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
		screenFovea.UnitTest();
		screenInput.UnitTest();
		audioInput.UnitTest();
		audioOut.UnitTest();
		cameraInput.UnitTest();
		textIn.UnitTest();
		textOut.UnitTest();
		whiteboardIn.UnitTest();
		whiteboardOut.UnitTest();
	}

	void Brain::AddMap(shared_ptr<SRSUnit> m) {
		conceptMaps[m->MapName] = m;
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
		for (std::pair<std::string, std::shared_ptr<SRSUnit>> u : conceptMaps)
			u.second->PostCreate(*this);
	}

	optional<shared_ptr<SRSUnit>> Brain::FindMapByName(string n) {
		auto m = conceptMaps.find(n);
		if (m != conceptMaps.end()) {
			return m->second;
		}
		return std::nullopt;
	}

}