#pragma once
#include "pch.h"
#include "ClassPredefines.h"

#include <list>
#include <string>
#include "SRSUnit.h"
#include "IO/ScreenInput.h"

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

		ScreenInput screenInput;

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
	};

}

