#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

#include "PatternMatchingSystem.h"
#include "GoodnessFunction.h"
#include "ConnectivityTriple.h"

namespace SRS22 {

	class SRSUnit
	{
		static unsigned short nextUID;
	public:

		std::vector<std::shared_ptr<SRSUnit>> nearMaps;
		std::vector<std::shared_ptr<SRSUnit>> farMaps;

		const unsigned short UID;
		/// <summary>
		/// Brain location, 3D. Concept relevance location.
		/// </summary>
		const cv::Vec3f location;

		const ConnectivityTriple ctrip;

		PatternMatchingSystem matchSystem;
		GoodnessFunction goodnessFunc;
		ConceptState M;

		SRSUnit(ConnectivityTriple ctrip, cv::Vec3f location, int w);
		SRSUnit(ConnectivityTriple ctrip, cv::Vec3f location, int w, int h);
		SRSUnit(ConnectivityTriple ctrip, cv::Vec3f location, int w, int h, int d);

		~SRSUnit();

		/// <summary>
		/// Called after all SRSUnits have been created and added to the Brain.
		/// This is where we cache all the precalculated nearMaps and farMaps
		/// </summary>
		void PostCreate(Brain& b);

		const int size();

		virtual void ProcessIO();
	};

}
