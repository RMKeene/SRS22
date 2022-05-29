#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

#include "PatternMatchingSystem.h"
#include "GoodnessFunction.h"
#include "ConnectivityTriple.h"
#include "TransformFunction.h"

namespace SRS22 {

	class SRSUnit
	{
		static unsigned short nextUID;
	public:
		std::string MapName;
		std::string MapDescription;

		std::vector<std::shared_ptr<SRSUnit>> nearMaps;
		std::vector<std::shared_ptr<SRSUnit>> farMaps;

		const unsigned short UID;
		/// <summary>
		/// Brain location, 3D. Concept relevance location.
		/// </summary>
		const cv::Vec3f location;

		const ConnectivityTriple ctrip;

		PatternMatchingSystem matchSystem;
		std::shared_ptr<GoodnessFunction> goodnessFunc;

		ConceptState M;
		ConceptState nextM;

		/// <summary>
		/// The MapName is almost always the class name of the sub-class, e.g. "ScreenFoveaMap"
		/// </summary>
		/// <param name="MapName"></param>
		/// <param name="ctrip"></param>
		/// <param name="location"></param>
		/// <param name="cols"></param>
		/// <param name="MapDescription"></param>
		SRSUnit(std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int cols, std::string MapDescription);
		SRSUnit(std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int rows, int cols, std::string MapDescription);
		SRSUnit(std::string MapName, ConnectivityTriple ctrip, cv::Vec3f location, int layers, int rows, int cols, std::string MapDescription);

		~SRSUnit();

		/// <summary>
		/// Called after all SRSUnits have been created and added to the Brain.
		/// This is where we cache all the precalculated nearMaps and farMaps
		/// </summary>
		void PostCreate(Brain& b);

		/// <summary>
		/// return M.charges.size();
		/// </summary>
		/// <returns></returns>
		const cv::MatSize matSize();
		const int entriesCount();
		const int byteCount();

		/// <summary>
		/// Process all inputs and system state, comapre patterns, do transforms.
		/// Do NOT change M, just cache next M state. Gets called in parallel for all SRSUnits.
		/// </summary>
		virtual void ComputeNextState();

		/// <summary>
		/// After processIO has been called on all SRSUnits, this gets called to transfer the nextM state to M.
		/// Gets called in parallel for all SRSUnits. So must be just state transfer inside the SRSUnit.
		/// This is NOT the place to do any post processing on the next state!
		/// </summary>
		virtual void LatchNewState();

		virtual std::string Debug();
	};

}
