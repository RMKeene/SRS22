#include "SRS22pch.h"
#include <fstream>
#include "Brain.h"
#include "Cortex.h"
#include "ConceptMap.h"
#include "GlobalWorld.h"
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

	boolean Brain::doParallel = true;

	Brain::Brain() {
		overallGoodness = 0;
		overallGoodnessPrevious = 0;
		overallGoodnessRateOfChange = 0;
		tickCount = 0;
		tickCountRecent = 0;
		SingleStepCount = 0;
		cortex = new Cortex(*this);
	}

	Brain::~Brain() {
	}

	void Brain::put(int idx, float val) { cortex->put(idx, val); }
	float Brain::get(int idx) { return cortex->get(idx); }

	void Brain::putNext(int idx, float val) { cortex->putNext(idx, val); }
	float Brain::getNext(int idx) { return cortex->getNext(idx); }



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
		TickConceptMaps();
		cortex->ResetStats();
		cortex->ComputeNextState(doParallel);
		cortex->LatchNewState(doParallel);
		ReSetupMatricMirrors();
		cortex->LearningPhase(doParallel);
		cortex->PostProcessStats();
		TickGoodnessLevels();
		PostTickHardwareAndUI();
	}

	void Brain::TickGoodnessLevels()
	{
		// Endorphins feeling of good. Causes learning rate to rise. A cool idea but not yet used?
		overallGoodnessRateOfChange = overallGoodnessRateOfChange * 0.95f + overallGoodness - overallGoodnessPrevious;
		overallGoodness *= 0.98f;
		overallGoodnessPrevious = overallGoodness;
	}

	void Brain::TickConceptMaps()
	{
		if (doParallel) {
			parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::pair<MapUidE, std::shared_ptr<ConceptMap>> n) {
				if (n.second->isComputeNextStateEnabled()) {
					n.second->ComputeNextState(false);
				}
				});
		}
		else {
			for (std::pair<MapUidE, std::shared_ptr<ConceptMap>> n : conceptMaps) {
				if (n.second->isComputeNextStateEnabled()) {
					n.second->ComputeNextState(false);
				}
			}
		}
	}

	void Brain::ReSetupMatricMirrors()
	{
		if (doParallel) {
			parallel_for_each(begin(conceptMaps), end(conceptMaps), [&](std::pair<MapUidE, std::shared_ptr<ConceptMap>> n) {
				n.second->setupCVMatMirrors();
				});
		}
		else {
			for (std::pair<MapUidE, std::shared_ptr<ConceptMap>> n : conceptMaps) {
				n.second->setupCVMatMirrors();
			}
		}
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

	pair<bool, string> Brain::Load(string fileName) const {
		SRS22LogTaker::LogInfo(std::format("Loading Brain from {}", fileName).c_str());
		std::ifstream file(fileName, std::ios::binary);
		if (!file.is_open()) {
			SRS22LogTaker::LogError(std::format("File not found: {}", fileName).c_str());
			return { false, "File not found." };
		}
		int totalNeurons = 0;
		int neuronHistory = NEURON_HISTORY;
		// In the future this will be how accurate of charge we keep. Like std::float16_t, float, double, etc.
		float chargePrecision = 1.0f;
		int neuronOutputs;
		file.read(reinterpret_cast<char*>(&totalNeurons), sizeof(int));
		file.read(reinterpret_cast<char*>(&neuronHistory), sizeof(int));
		file.read(reinterpret_cast<char*>(&chargePrecision), sizeof(float));
		file.read(reinterpret_cast<char*>(&neuronOutputs), sizeof(int));
		if (totalNeurons != TOTAL_NEURONS || neuronHistory != NEURON_HISTORY || chargePrecision != sizeof(float) || neuronOutputs != NEURON_OUTPUTS) {
			// TODO - Make it work for larger configuration.
			// TODO - Make it work for smaller configuration.
			return { false, "File does not match current Brain configuration." };
		}
		Neurons&Ns = cortex->neurons;
		file.read(reinterpret_cast<char*>(Ns.charge), sizeof(Ns.charge));
		file.read(reinterpret_cast<char*>(Ns.neuronChargesAverageDeltaSum), sizeof(Ns.neuronChargesAverageDeltaSum));
		file.read(reinterpret_cast<char*>(Ns.neuronChargesAverageCount), sizeof(Ns.neuronChargesAverageCount));
		file.read(reinterpret_cast<char*>(Ns.energy), sizeof(Ns.energy));
		file.read(reinterpret_cast<char*>(Ns.enabled), sizeof(Ns.enabled));
		file.read(reinterpret_cast<char*>(Ns.link), sizeof(Ns.link));


		file.close();
		SRS22LogTaker::LogInfo(std::format("Brain loaded from {}", fileName).c_str());
		return { true, "" };
	}

	bool Brain::Store(string fileName) const {
		SRS22LogTaker::LogInfo(std::format("Storing Brain to {}", fileName).c_str());
		std::ofstream file(fileName, std::ios::binary);
		if (!file.is_open()) {
			SRS22LogTaker::LogError(std::format("Unable to open: {}", fileName).c_str());
			return false;
		}
		// Store the cortex neuronCharges array in binary
		int totalNeurons = TOTAL_NEURONS;
		int neuronHistory = NEURON_HISTORY;
		int neuronOutputs = NEURON_OUTPUTS;
		float chargePrecision = sizeof(float);

		file.write(reinterpret_cast<char*>(&totalNeurons), sizeof(int));
		file.write(reinterpret_cast<char*>(&neuronHistory), sizeof(int));
		file.write(reinterpret_cast<char*>(&chargePrecision), sizeof(float));
		file.write(reinterpret_cast<char*>(&neuronOutputs), sizeof(int));

		Neurons& Ns = cortex->neurons;
		file.write(reinterpret_cast<char*>(Ns.charge), sizeof(Ns.charge));
		file.write(reinterpret_cast<char*>(Ns.neuronChargesAverageDeltaSum), sizeof(Ns.neuronChargesAverageDeltaSum));
		file.write(reinterpret_cast<char*>(Ns.neuronChargesAverageCount), sizeof(Ns.neuronChargesAverageCount));
		file.write(reinterpret_cast<char*>(Ns.energy), sizeof(Ns.energy));
		file.write(reinterpret_cast<char*>(Ns.enabled), sizeof(Ns.enabled));
		file.write(reinterpret_cast<char*>(Ns.link), sizeof(Ns.link));

		file.close();
		SRS22LogTaker::LogInfo(std::format("Brain stored to {}", fileName).c_str());
		return true;
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
		std::pair<int, int> cortexOffsets = ioMapToContext.addMapping(m->MapName, m->totalSize);
		m->cortexStartIndex = cortexOffsets.first;
		m->setupCVMatMirrors();
		conceptMaps[m->UID] = m;
		conceptMapsByName[m->MapName] = m;
		printf("Added ConceptMap %s at %d to %d\n", m->MapName.c_str(), cortexOffsets.first, cortexOffsets.second - 1);
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

	string Brain::FindMapByCortexIdx(int idx) {
		BrainH b = GlobalWorld::GlobalWorldInstance.brains[0];
		for (std::pair<MapUidE, std::shared_ptr<ConceptMap>> u : b->conceptMaps) {
			if (idx >= u.second->cortexStartIndex && idx < u.second->cortexStartIndex + u.second->totalSize) {
				return u.second->MapName;
			}
		}
		return std::format("{} index not in any map.", idx);
	}
}