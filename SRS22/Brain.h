#pragma once
#include "SRS22pch.h"

#include <string>
#include "ConceptArray.h"
#include "HardwareIO/ScreenInputIO.h"
#include "HardwareIO/AudioCaptureIO.h"
#include "HardwareIO/AudioOutIO.h"
#include "HardwareIO/CameraInIO.h"
#include "HardwareIO/TextInIO.h"
#include "HardwareIO/TextOutIO.h"
#include "HardwareIO/WhiteboardInIO.h"
#include "HardwareIO/WhiteboardOutIO.h"
#include "HardwareIO/ScreenAttnSpotIO.h"
#include "HardwareIO/CameraAttnSpotIO.h"
#include "HardwareIO/PhonemesIO.h"
#include "Histogram.h"
#include "IOMapToCortext.h"
#include <rpcndr.h>
#include <map>

namespace SRS22 {
	using namespace std;

	class Cortex;
	class ConceptArray;

	class Brain
	{
	public:

		IOMapToContext ioMapToContext;

		/// <summary>
		/// Top level processing loop flag.
		/// </summary>
		static  boolean doParallel;

		/// <summary>
		/// Never depend on iteration order of maps. They are multi-thread processed and in a hash table.
		/// </summary>
		map<ArrayUidE, std::shared_ptr<ConceptArray>> conceptArrays;
		map<std::string, std::shared_ptr<ConceptArray>> conceptArraysByName;

		long long tickCount = 0;
		long long tickCountRecent = 0;
		int ticksPerSecondLatest = 1;

		/// <summary>
		/// 0 is stopped, -1 is free run, 1 or more is steps to do.
		/// If -1 then free run. Else step this many times, usually 1, down to 0 then stop.
		/// Assumes Tick() is getting called frequently.
		/// </summary>
		int SingleStepCount = 0;

		float baseLEarningRate = 0.001f;
		float learningRate = 0.001f;

		/// <summary>
		/// How good the system feels. + is good, - is bad, range about -1 to 1
		/// </summary>
		float overallGoodness = 0.0f;  
		float overallGoodnessPrevious = 0.0f; 
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

		Cortex* cortex;

		Histogram neuronChargeHist;
		Histogram neuronEnergyHist;
		Histogram linkWeightHist;
		Histogram linkActivityHist;
		Histogram linkAgeHist;
		Histogram linkConfidenceHist;

		Brain();
		~Brain();

		void put(int idx, float val);
		float get(int idx);

		void putNext(int idx, float val);
		float getNext(int idx);

		inline boolean ShouldLearn() const { return overallGoodnessRateOfChange >= overallGoodnessRateOfChangeThreshold; }

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

		pair<bool, string> Load(string fileName) const;
		bool Store(string fileName) const;

		void PostCreateAllConceptArrays();
		void PostCreateAllCortexChunks();

		optional<shared_ptr<ConceptArray>> FindMap(ArrayUidE n);
		optional<shared_ptr<ConceptArray>> FindMapByName(string n);

		/// <summary>
		/// The world for this brain is improving. Thus it should learn this state.
		/// </summary>
		/// <returns></returns>
		bool TheWorldIsGettingBetter() const { return overallGoodnessRateOfChange > overallGoodnessRateOfChangeThreshold; }
		/// <summary>
		/// Tell the brain it just did something good. From button on the UI
		/// </summary>
		void GoodJob() { overallGoodness += 0.5f; }
		/// <summary>
		/// Tell the brain it just did something bad.From button on the UI
		/// </summary>
		void BadJob() { overallGoodness -= 0.5f; }

		/// <summary>
		/// Find a ConceptArray by the index in the Cortex.
		/// Assumes you mean Brain[0].cortex.
		/// </summary>
		/// <param name="idx"></param>
		/// <returns></returns>
		static string FindArrayByCortexIdx(int idx);


	private:
		// PreTick(), ComputeNextState(), LatchNewState(), PostTick() etc.
		// This is where multiprocessor parallelism happens.
		void SequenceCoreBrainTick();
		void TickGoodnessLevels();
		void TickConceptArrays();
		void ReSetupMatrixMirrors();
		void PreTickHardwareAndIO();
		void PostTickHardwareAndUI();

		/// <summary>
		/// Order of adding maps does not matter. Never depend on iteration order.
		/// </summary>
		/// <param name="m"></param>
		void AddArray(std::shared_ptr<ConceptArray> m);
	};

	typedef std::shared_ptr<Brain> BrainH;
}
