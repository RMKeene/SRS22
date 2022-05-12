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
		ConceptState nextM;

		SRSUnit(ConnectivityTriple ctrip, cv::Vec3f location, int w);
		SRSUnit(ConnectivityTriple ctrip, cv::Vec3f location, int w, int h);
		SRSUnit(ConnectivityTriple ctrip, cv::Vec3f location, int w, int h, int d);

		~SRSUnit();

		/// <summary>
		/// Called after all SRSUnits have been created and added to the Brain.
		/// This is where we cache all the precalculated nearMaps and farMaps
		/// </summary>
		void PostCreate(Brain& b);

		/// <summary>
		/// return M.size();
		/// </summary>
		/// <returns></returns>
		const int size();

		/// <summary>
		/// Process all inputs and system state, comapre patterns, do transforms.
		/// Do NOT change M, just cache next M state. Gets called in parallel for all SRSUnits.
		/// </summary>
		virtual void ComputeNextState();

		/// <summary>
		/// After processIO has been called on all SRSUnits, this gets called to transfer the nextM state to M.
		/// Gets called in parallel for all SRSUnits. So must be just state transfer inside the SRSUnit.
		/// </summary>
		virtual void LatchNewState();
	};

}
