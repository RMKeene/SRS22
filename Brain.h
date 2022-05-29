#pragma once
#include "pch.h"
#include "ClassPredefines.h"

#include <list>
#include <string>
#include "SRSUnit.h"
#include "HardwareIO/ScreenInputIO.h"
#include "HardwareIO/AudioCaptureIO.h"
#include "HardwareIO/WaveInputHelper.h"
#include "HardwareIO/WaveOutputHelper.h"
#include "HardwareIO/AudioOutIO.h"
#include "HardwareIO/CameraInIO.h"
#include "HardwareIO/TextInIO.h"
#include "HardwareIO/TextOutIO.h"
#include "HardwareIO/WhiteboardInIO.h"
#include "HardwareIO/WhiteboardOutIO.h"
#include "HardwareIO/ScreenAttnSpotIO.h"

namespace SRS22 {
	using namespace std;

	class Brain
	{
	public:
		map<std::string, std::shared_ptr<SRSUnit>> conceptMaps;

		/// <summary>
		/// Threshold for ConnectivityTriple that defines range B.
		/// If distance of ConceptMap <= maxNearDistance thern it is in B range,
		/// if >= minFarDistance then it is range C.
		/// </summary>
		float maxNearDistance = 50.0f;
		float minFarDistance = 100.0f;

		/// <summary>
		/// If -1 the free run. Else step this many times, usualy 1, down to 0 then stop.
		/// Assumes Tick() is getting called frequently.
		/// </summary>
		int SingleStepCount = -1;

		AudioCaptureIO audioInput;
		AudioOutIO audioOut;
		CameraInIO cameraInput;
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

		void Tick();

		pair<bool, string> Load(string fileName);
		bool Store(string fileName);

		std::optional<PatternConnection> GetRandomNeuron(shared_ptr<SRSUnit> origin);

		void PostCreateAllSRSUnits();


	private:
		void PreTick();
		void PostTick();

		void AddMap(shared_ptr<SRSUnit> m);

	};

}

