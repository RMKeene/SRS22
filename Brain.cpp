#include "pch.h"
#include "Brain.h"
#include "ConceptMap.h"
#include "FastRand.h"
#include <tchar.h>
#include <ppl.h>
#include "Maps/Screen/ScreenFoveaMap.h"
#include "Maps/Screen/ScreenAttnSpotMap.h"
#include "Maps/Screen/ScreenDifferenceMap.h"
#include "Maps/Screen/ScreenMotionXYMap.h"
#include "Maps/RandomMap.h"
#include "Maps/Camera/CameraFoveaMap.h"
#include "Maps/Camera/CameraAttnSpotMap.h"
#include "Maps/Camera/CameraDifferenceMap.h"
#include "Maps/Camera/CameraMotionXYMap.h"
#include "Maps/Text/TextCurrentCharMap.h"
#include "Maps/Text/TextOutMap.h"
#include "Maps/Draw/DrawOutMap.h"
#include "Maps/Draw/DrawInMap.h"
#include "Maps/Voice/PhonemeMap.h"
#include "Maps/Hearing/HearingMap.h"

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

		parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::pair<MapUidE, std::shared_ptr<ConceptMap>> n) {
			n.second->ComputeNextState();
			});
		parallel_for_each(begin(cortexChunks), end(cortexChunks), [&](std::shared_ptr<CortexChunk> n) {
			n->ComputeNextState();
			});

		parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::pair<MapUidE, std::shared_ptr<ConceptMap>> n) {
			n.second->LatchNewState();
			});
		parallel_for_each(begin(cortexChunks), end(cortexChunks), [&](std::shared_ptr<CortexChunk> n) {
			n->LatchNewState();
			});

		PostTick();

		tickCount++;
		// Used for ticks per second over in MonitorFrame::OnMonitorFrameTickTimer
		tickCountRescent++;
	}

	void Brain::PreTick() {
		screenInput.PreTick();
		screenFovea.PreTick();
		audioInput.PreTick();
		audioOut.PreTick();
		cameraInput.PreTick();
		cameraFovea.PreTick();
		phonemesOut.PreTick();
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
		phonemesOut.PostTick();
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

	void Brain::Init() {
		// Hardware I/O setups.
		screenInput.Init();
		audioInput.Init();
		audioOut.Init();
		cameraInput.Init();
		phonemesOut.Init();
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

		AddMap(make_shared<DrawInMap>(this));
		AddMap(make_shared<DrawOutMap>(this));

		AddMap(make_shared<HearingMap>(this));

		AddMap(make_shared<PhonemeMap>(this));

		AddMap(make_shared<RandomMap>(this));

		AddMap(make_shared<ScreenAttnSpotMap>(this));
		AddMap(make_shared<ScreenDifferenceMap>(this));
		AddMap(make_shared<ScreenFoveaMap>(this));
		AddMap(make_shared<ScreenMotionXYMap>(this));

		AddMap(make_shared<TextCurrentCharMap>(this));
		AddMap(make_shared<TextOutMap>(this));

		// The Cortex
		AddCortexChunk(make_shared<CortexChunk>(cv::Vec3f(0, 0, 0), 1000, ConnectivityTriple(0.1f, 0.6f, 0.3f, 40), 0.02f));

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

	void Brain::AddMap(shared_ptr<ConceptMap> m) {
		conceptMaps[m->UID] = m;
		conceptMapsByName[m->MapName] = m;
	}

	void Brain::AddCortexChunk(shared_ptr<CortexChunk> c) {
		cortexChunks.push_back(c);
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
		for (std::pair<MapUidE, std::shared_ptr<ConceptMap>> u : conceptMaps)
			u.second->PostCreate(*this);
	}

	optional<shared_ptr<ConceptMap>> Brain::FindMap(MapUidE n) {
		auto m = conceptMaps.find(n);
		if (m != conceptMaps.end()) {
			return m->second;
		}
		return std::nullopt;
	}

	optional<shared_ptr<ConceptMap>> Brain::FindMapByName(string n) {
		auto m = conceptMapsByName.find(n);
		if (m != conceptMapsByName.end()) {
			return m->second;
		}
		return std::nullopt;
	}

	bool Brain::GetRandomConnectionPoint(CortexChunk& from, const int fromOffset, const ConnectivityTriple& ct, const cv::Vec3f& location,
		/* Out */ PatternConnection& outConnection) {

		int antiLockupCount = 4;

		do {
			antiLockupCount--;

			const float r = fastRandFloat();
			if (r < ct.selfFract) { // Self connection
				outConnection.target = &from;
				outConnection.linearOffset = from.GetRandomLinearOffset();
			}
			else if (r < ct.selfFract + ct.nearbyFract && from.nearChunks.size() > 0) { // Nearby connection
				const float fracNth = fastRandFloat() * from.nearChunks.size();
				int nth = (int)fracNth;
				outConnection.target = nullptr;
				for (auto it = from.nearChunks.begin(); it != from.nearChunks.end() && nth > 0; it++) {
					outConnection.target = it->get();
					nth--;
				}
			}
			else if (from.farChunks.size() > 0) { // Far connection
				const float fracNth = fastRandFloat() * from.farChunks.size();
				int nth = (int)fracNth;
				outConnection.target = nullptr;
				for (auto it = from.farChunks.begin(); it != from.farChunks.end() && nth > 0; it++) {
					outConnection.target = it->get();
					nth--;
				}
			}
		} while (
			(PatternConnection::equals(outConnection, &from, fromOffset) 
				|| !outConnection.target->isConnectableFlag
				// The check that concept space Z is less than from's Z is already checked when near and far lists are filled.
				)
			&& antiLockupCount > 0);

		return antiLockupCount > 0;
	}
}