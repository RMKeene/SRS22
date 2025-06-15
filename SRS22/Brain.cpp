#include "SRS22pch.h"
#include <fstream>
#include "Brain.h"
#include "Cortex.h"
#include "ConceptArray.h"
#include "GlobalWorld.h"
#include <ppl.h>
#include "Maps/Screen/ScreenFoveaArray.h"
#include "Maps/Screen/ScreenAttnSpotArray.h"
#include "Maps/Screen/ScreenDifferenceArray.h"
#include "Maps/Screen/ScreenMotionXYArray.h"
#include "Maps/RandomArray.h"
#include "Maps/Camera/CameraFoveaArray.h"
#include "Maps/Camera/CameraAttnSpotArray.h"
#include "Maps/Camera/CameraDifferenceArray.h"
#include "Maps/Camera/CameraMotionXYArray.h"
#include "Maps/Text/TextCurrentCharArray.h"
#include "Maps/Text/TextOutArray.h"
#include "Maps/Draw/DrawOutArray.h"
#include "Maps/Draw/DrawInArray.h"
#include "Maps/Voice/PhonemeArray.h"
#include "Maps/Hearing/HearingArray.h"
#include "Maps/Camera/CameraFoveaAngleArray.h"
#include "Maps/Camera/CameraFoveaEdgesArray.h"
#include "Maps/Camera/CameraFoveaAbsDiffArray.h"

using namespace concurrency;

namespace SRS22 {
	using namespace std;

	boolean Brain::doParallel = true;

	Brain::Brain() {
		remove("cortex_log.txt");
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
		TickConceptArrays();
		cortex->ResetStats();

		cortex->ComputeNextState(doParallel);
		cortex->LearningPhase(doParallel);
		cortex->LatchNewState(doParallel);
		ReSetupMatrixMirrors();

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

	void Brain::TickConceptArrays()
	{
		if (doParallel) {
			parallel_for_each(begin(conceptArrays), end(conceptArrays), [&](std::pair<ArrayUidE, std::shared_ptr<ConceptArray>> n) {
				n.second->ComputeNextState(false);
				});
		}
		else {
			for (std::pair<ArrayUidE, std::shared_ptr<ConceptArray>> n : conceptArrays) {
				n.second->ComputeNextState(false);
			}
		}
	}

	void Brain::ReSetupMatrixMirrors()
	{
		if (doParallel) {
			parallel_for_each(begin(conceptArrays), end(conceptArrays), [&](std::pair<ArrayUidE, std::shared_ptr<ConceptArray>> n) {
				n.second->setupCVMatMirrors();
				});
		}
		else {
			for (std::pair<ArrayUidE, std::shared_ptr<ConceptArray>> n : conceptArrays) {
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
		try {
			file.read(reinterpret_cast<char*>(&totalNeurons), sizeof(int));
			file.read(reinterpret_cast<char*>(&neuronHistory), sizeof(int));
			file.read(reinterpret_cast<char*>(&chargePrecision), sizeof(float));
			file.read(reinterpret_cast<char*>(&neuronOutputs), sizeof(int));
			if (totalNeurons != TOTAL_NEURONS || neuronHistory != NEURON_HISTORY || chargePrecision != sizeof(float) || neuronOutputs != NEURON_UPSTREAM_LINKS) {
				// TODO - Make it work for larger configuration.
				// TODO - Make it work for smaller configuration.
				return { false, "File does not match current Brain configuration." };
			}
			Neurons& Ns = cortex->neurons;
			file.read(reinterpret_cast<char*>(Ns.charge), sizeof(Ns.charge));
			file.read(reinterpret_cast<char*>(Ns.energyCeiling), sizeof(Ns.energyCeiling));
			file.read(reinterpret_cast<char*>(Ns.neuronChargesAverageCount), sizeof(Ns.neuronChargesAverageCount));
			file.read(reinterpret_cast<char*>(Ns.link), sizeof(Ns.link));

			file.read(reinterpret_cast<char*>(&cortex->settings), sizeof(CortexSettings));

		}
		catch (std::exception e) {
			SRS22LogTaker::LogError(std::format("Error loading Brain from {}: {}", fileName, e.what()).c_str());
			file.close();
			return { false, e.what() };
		}

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
		try {
			// Store the cortex neuronCharges array in binary
			int totalNeurons = TOTAL_NEURONS;
			int neuronHistory = NEURON_HISTORY;
			int neuronOutputs = NEURON_UPSTREAM_LINKS;
			float chargePrecision = sizeof(float);

			file.write(reinterpret_cast<char*>(&totalNeurons), sizeof(int));
			file.write(reinterpret_cast<char*>(&neuronHistory), sizeof(int));
			file.write(reinterpret_cast<char*>(&chargePrecision), sizeof(float));
			file.write(reinterpret_cast<char*>(&neuronOutputs), sizeof(int));

			Neurons& Ns = cortex->neurons;
			file.write(reinterpret_cast<char*>(Ns.charge), sizeof(Ns.charge));
			file.write(reinterpret_cast<char*>(Ns.energyCeiling), sizeof(Ns.energyCeiling));
			file.write(reinterpret_cast<char*>(Ns.neuronChargesAverageCount), sizeof(Ns.neuronChargesAverageCount));
			file.write(reinterpret_cast<char*>(Ns.link), sizeof(Ns.link));

			file.write(reinterpret_cast<char*>(&cortex->settings), sizeof(CortexSettings));
		}
		catch (std::exception e) {
			SRS22LogTaker::LogError(std::format("Error storing Brain to {}: {}", fileName, e.what()).c_str());
			file.close();
			return false;
		}

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

		// All ConceptArray instances. Keep in alphabetical order please. 
		// These calls also set the layout in linear space in the Cortex.
		// So any additions in the middle will break disk saves.
		AddArray(make_shared<CameraAttnSpotArray>(this));
		AddArray(make_shared<CameraDifferenceArray>(this));
		AddArray(make_shared<CameraFoveaAngleArray000>(this));
		AddArray(make_shared<CameraFoveaAngleArray225>(this));
		AddArray(make_shared<CameraFoveaAngleArray450>(this));
		AddArray(make_shared<CameraFoveaAngleArray675>(this));
		AddArray(make_shared<CameraFoveaAngleArray900>(this));
		AddArray(make_shared<CameraFoveaAngleArray1125>(this));
		AddArray(make_shared<CameraFoveaAngleArray1350>(this));
		AddArray(make_shared<CameraFoveaAngleArray1575>(this));
		AddArray(make_shared<CameraFoveaAbsDiffArray>(this));
		AddArray(make_shared<CameraFoveaEdgesArray>(this));
		AddArray(make_shared<CameraFoveaArray>(this));
		AddArray(make_shared<CameraMotionXYArray>(this));

		AddArray(make_shared<DrawInArray>(this));
		AddArray(make_shared<DrawOutArray>(this));

		AddArray(make_shared<HearingArray>(this));

		AddArray(make_shared<PhonemeArray>(this));

		AddArray(make_shared<RandomArray>(this));

		AddArray(make_shared<ScreenAttnSpotArray>(this));
		AddArray(make_shared<ScreenDifferenceArray>(this));
		AddArray(make_shared<ScreenFoveaArray>(this));
		AddArray(make_shared<ScreenMotionXYArray>(this));

		AddArray(make_shared<TextCurrentCharArray>(this));
		AddArray(make_shared<TextOutArray>(this));

		// Compile the SRS system relationships.
		PostCreateAllConceptArrays();
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

	void Brain::AddArray(shared_ptr<ConceptArray> m) {
		// open append file:
		std::ofstream f("cortex_log.txt", std::ios::app);
		if (conceptArrays.find(m->UID) != conceptArrays.end())
			throw std::exception((std::string("Duplicate ConceptArray UID in Brain::AddArray: ") + m->ArrayName).c_str());
		std::pair<int, int> cortexOffsets = ioMapToContext.addMapping(m->ArrayName, m->totalSize);
		m->cortexStartIndex = cortexOffsets.first;
		m->setupCVMatMirrors();
		conceptArrays[m->UID] = m;
		conceptArraysByName[m->ArrayName] = m;
		std::string ss;
		if(m->neuronType == NeuronType::IS_INPUT)
			ss = std::format("Added ConceptArray {} at {} to {} INPUT\n", m->ArrayName.c_str(), cortexOffsets.first, cortexOffsets.second - 1);
		else if (m->neuronType == NeuronType::IS_OUTPUT)
			ss = std::format("Added ConceptArray {} at {} to {} OUTPUT\n", m->ArrayName.c_str(), cortexOffsets.first, cortexOffsets.second - 1);
		else
			ss = std::format("Added ConceptArray {} at {} to {} REGULAR\n", m->ArrayName.c_str(), cortexOffsets.first, cortexOffsets.second - 1);
		f.write(ss.c_str(), ss.size());
		f.close();
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

	void Brain::PostCreateAllConceptArrays() {
		for (std::pair<ArrayUidE, std::shared_ptr<ConceptArray>> u : conceptArrays)
			u.second->PostCreate(*this);
	}

	void Brain::PostCreateAllCortexChunks() {
		cortex->PostCreate();
	}

	optional<shared_ptr<ConceptArray>> Brain::FindMap(ArrayUidE n) {
		auto m = conceptArrays.find(n);
		if (m != conceptArrays.end()) {
			return m->second;
		}
		return std::nullopt;
	}

	optional<shared_ptr<ConceptArray>> Brain::FindMapByName(string n) {
		auto m = conceptArraysByName.find(n);
		if (m != conceptArraysByName.end()) {
			return m->second;
		}
		return std::nullopt;
	}

	string Brain::FindArrayByCortexIdx(int idx) {
		BrainH b = GlobalWorld::GlobalWorldInstance.brains[0];
		for (std::pair<ArrayUidE, std::shared_ptr<ConceptArray>> u : b->conceptArrays) {
			if (idx >= u.second->cortexStartIndex && idx < u.second->cortexStartIndex + u.second->totalSize) {
				return u.second->ArrayName;
			}
		}
		return std::format("{} index not in any map.", idx);
	}
}