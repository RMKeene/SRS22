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
#include "Maps/Camera/CameraFoveaAngleMap.h"
#include "Maps/Camera/CameraFoveaEdgesMap.h"
#include "Maps/Camera/CameraFoveaAbsDiffMap.h"

using namespace concurrency;

namespace SRS22 {
	using namespace std;

	Brain::Brain() {
		overallGoodness = 0;
		overallGoodnessPrevious = 0;
		overallGoodnessRateOfChange = 0;
		tickCount = 0;
		tickCountRecent = 0;
		SingleStepCount = -1;
		cortex = new Cortex(*this, 0.02f);
	}

	Brain::~Brain() {
	}

	void Brain::Tick() {
		if (SingleStepCount == 0)
			return;
		if (SingleStepCount > 0)
			SingleStepCount--;

		SequenceCoreBrainTick();

		tickCount++;
		// Used for ticks per second over in MonitorFrame::OnMonitorFrameTickTimer
		tickCountRecent++;
	}

	void Brain::SequenceCoreBrainTick()
	{
		PreTickHardwareAndIO();

		if (tickCount == 14)
			printf("");

		//for (std::pair<MapUidE, std::shared_ptr<ConceptMap>> n : conceptMaps) {
		//	n.second->ComputeNextState();
		//}

		parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::pair<MapUidE, std::shared_ptr<ConceptMap>> n) {
			n.second->ComputeNextState();
			});

		cortex->ComputeNextState();
		cortex->LatchNewState();
		cortex->LatchNewState();
		cortex->LearningPhase();

		overallGoodnessRateOfChange = overallGoodnessRateOfChange * 0.95f + overallGoodness - overallGoodnessPrevious;
		overallGoodness *= 0.98f;
		overallGoodnessPrevious = overallGoodness;

		PostTickHardwareAndUI();
	}

	void Brain::PreTickHardwareAndIO() {
		screenInput.PreTickHardwareAndIO();
		screenFovea.PreTickHardwareAndIO();
		audioInput.PreTickHardwareAndIO();
		audioOut.PreTickHardwareAndIO();
		cameraInput.PreTickHardwareAndIO();
		cameraFovea.PreTickHardwareAndIO();
		phonemesOut.PreTickHardwareAndIO();
		textIn.PreTickHardwareAndIO();
		textOut.PreTickHardwareAndIO();
		whiteboardIn.PreTickHardwareAndIO();
		whiteboardOut.PreTickHardwareAndIO();
	}

	void Brain::PostTickHardwareAndUI() {
		screenFovea.PostTickHardwareAndUI();
		screenInput.PostTickHardwareAndUI();
		audioInput.PostTickHardwareAndUI();
		audioOut.PostTickHardwareAndUI();
		cameraFovea.PostTickHardwareAndUI();
		cameraInput.PostTickHardwareAndUI();
		phonemesOut.PostTickHardwareAndUI();
		textIn.PostTickHardwareAndUI();
		textOut.PostTickHardwareAndUI();
		whiteboardIn.PostTickHardwareAndUI();
		whiteboardOut.PostTickHardwareAndUI();
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

		// All Map instances. Keep in alphabetical order please. These calls also set the layout in linear space in the Cortex.
		// So any additions in the middle will break disk saves.
		AddMap(make_shared<CameraAttnSpotMap>(this));
		AddMap(make_shared<CameraDifferenceMap>(this));
		AddMap(make_shared<CameraFoveaAngleMap000>(this));
		AddMap(make_shared<CameraFoveaAngleMap225>(this));
		AddMap(make_shared<CameraFoveaAngleMap450>(this));
		AddMap(make_shared<CameraFoveaAngleMap675>(this));
		AddMap(make_shared<CameraFoveaAngleMap900>(this));
		AddMap(make_shared<CameraFoveaAngleMap1125>(this));
		AddMap(make_shared<CameraFoveaAngleMap1350>(this));
		AddMap(make_shared<CameraFoveaAngleMap1575>(this));
		AddMap(make_shared<CameraFoveaAbsDiffMap>(this));
		AddMap(make_shared<CameraFoveaEdgesMap>(this));
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

		// Compile the SRS system relationships.
		PostCreateAllConceptMaps();
	}

	void Brain::Shutdown() {
		screenFovea.Shutdown();
		screenInput.Shutdown();
		// audioInput.Shutdown(); // Hangs
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
		if (conceptMaps.find(m->UID) != conceptMaps.end())
			throw std::exception((std::string("Duplicate ConceptMap UID in Brain::AddMap: ") + m->MapName).c_str());
		int cortexOffset = ioMapToContext.addMapping(m->MapName, m->entriesCount());
		conceptMaps[m->UID] = m;
		conceptMapsByName[m->MapName] = m;
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

	void Brain::PostCreateAllConceptMaps() {
		for (std::pair<MapUidE, std::shared_ptr<ConceptMap>> u : conceptMaps)
			u.second->PostCreate(*this);
	}

	void Brain::PostCreateAllCortexChunks() {
		cortex->PostCreate();
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
}