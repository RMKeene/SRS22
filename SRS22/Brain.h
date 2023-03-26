#pragma once
#include "pch.h"
#include "ClassPredefines.h"

#include <list>
#include <string>
#include "ConceptMap.h"
#include "HardwareIO/ScreenInputIO.h"
#include "HardwareIO/AudioCaptureIO.h"
#include "HardwareRaw/WaveInputHelper.h"
#include "HardwareRaw/WaveOutputHelper.h"
#include "HardwareIO/AudioOutIO.h"
#include "HardwareIO/CameraInIO.h"
#include "HardwareIO/TextInIO.h"
#include "HardwareIO/TextOutIO.h"
#include "HardwareIO/WhiteboardInIO.h"
#include "HardwareIO/WhiteboardOutIO.h"
#include "HardwareIO/ScreenAttnSpotIO.h"
#include "HardwareIO/CameraAttnSpotIO.h"
#include "HardwareIO/PhonemesIO.h"
#include "CortexChunk.h"

namespace SRS22 {
	using namespace std;

	class Brain
	{
	public:
		map<MapUidE, std::shared_ptr<ConceptMap>> conceptMaps;
		map<std::string, std::shared_ptr<ConceptMap>> conceptMapsByName;
		std::list< std::shared_ptr<CortexChunk>> cortexChunks;

		/// <summary>
		/// Threshold for ConnectivityTriple that defines range B.
		/// If distance of ConceptMap <= maxNearDistance then it is in B range,
		/// if >= minFarDistance then it is range C.
		/// </summary>
		float maxNearDistance = 50.0f;
		float minFarDistance = 100.0f;

		long long tickCount = 0;
		long long tickCountRescent = 0;
		int ticksPerSecondLatest = 1;

		/// <summary>
		/// If -1 the free run. Else step this many times, usualy 1, down to 0 then stop.
		/// Assumes Tick() is getting called frequently.
		/// </summary>
		int SingleStepCount = 0;

		/// <summary>
		/// How good the system feels. + is good, - is bad, range about -1 to 1
		/// </summary>
		float overallGoodness = 0.0f;
		/// <summary>
		/// Tempered derivative of overallGoodness.
		/// </summary>
		float overallGoodnessRateOfChange = 0.0f;
		float overallGoodnessRateOfChangeThreshold = 0.1f;

		AudioCaptureIO audioInput;
		AudioOutIO audioOut;
		CameraAttnSpotIO cameraFovea;
		CameraInIO cameraInput;
		PhonemesIO phonemesOut;
		ScreenAttnSpotIO screenFovea;
		ScreenInputIO screenInput;
		TextInIO textIn;
		TextOutIO textOut;
		WhiteboardInIO whiteboardIn;
		WhiteboardOutIO whiteboardOut;

		Brain();
		~Brain();

		/// <summary>
		/// Called just before Win Main Message Loop starts iterating.
		/// </summary>
		void Init();
		void Shutdown();
		void UnitTest();

		/// <summary>
		/// Clamps n to 1 to 10000 range.
		/// </summary>
		/// <param name="n"></param>
		void DoNStep(int n);
		void DoSingleStep();
		void Pause();
		void Continue();

		/// <summary>
		/// The core Tick of the Brain called frequently. See Tickable for the phases of a Tick.
		/// This is where single stepping is controlled. Calls SequenceCoreBrainTick().
		/// </summary>
		void Tick();

		pair<bool, string> Load(string fileName);
		bool Store(string fileName);

		void PostCreateAllConceptMaps();
		void PostCreateAllCortexChunks();

		optional<shared_ptr<ConceptMap>> FindMap(MapUidE n);
		optional<shared_ptr<ConceptMap>> FindMapByName(string n);

		/// <summary>
		/// Find and return a random point (neuron) in the brain.
		/// - Uses ct to give the ratio of connection to far, near or self (from) neurons.
		/// - The result will have a BrainLocation lower or equal in Z in the brain.
		/// - Never returns outConnection equal to from.
		/// - outConnection will never be to a ConceptMap with a false isConnectable.
		/// </summary>
		/// <param name="ct"></param>
		/// <param name="lcation"></param>
		/// <param name="outConnection"></param>
		/// <returns>True on success.</returns>
		bool GetRandomConnectionPoint(CortexChunk& from, const int fromOffset,
			/* Out */ std::shared_ptr<PatternConnection> outConnection);

		/// <summary>
		/// The world for this brain is improving. Thus it should learn this state.
		/// </summary>
		/// <returns></returns>
		bool TheWorldIsGettingBetter() { return overallGoodnessRateOfChange > overallGoodnessRateOfChangeThreshold; }

	private:
		// PreTick(), ComputeNextState(), LatchNewState(), PostTick()
		// This is where multiprocessor parallelism happens.
		void SequenceCoreBrainTick();
		void PreTickHardwareAndIO();
		void PostTickHardwareAndUI();

		void AddMap(shared_ptr<ConceptMap> m);
		void AddCortexChunk(shared_ptr<CortexChunk> c);
	};

	typedef std::shared_ptr<Brain> BrainH;
}
