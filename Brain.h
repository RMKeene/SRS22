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

namespace SRS22 {
	using namespace std;

	class Brain
	{
	public:
		list<std::shared_ptr<SRSUnit>> conceptMaps;

		/// <summary>
		/// Threshold for ConnectivityTriple that defines range B.
		/// If distance of ConceptMap <= maxNearDistance thern it is in B range,
		/// if >= minFarDistance then it is range C.
		/// </summary>
		float maxNearDistance = 50.0f;
		float minFarDistance = 100.0f;

		ScreenInputIO screenInput;
		AudioCaptureIO audioInput;
		AudioOutIO audioOut;
		CameraInIO cameraInput;
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

		void Tick();

		pair<bool, string> Load(string fileName);
		bool Store(string fileName);

		std::optional<PatternConnection> GetRandomNeuron(shared_ptr<SRSUnit> origin);

		void PostCreateAllSRSUnits();

		void TakeScreenSnapshot();

	private:
		void PreTick();
		void PostTick();

	};

}

