#pragma once
#include "pch.h"
#include <opencv2/core.hpp>

#include "MapUIDs.h"
#include "PatternMatchingSystem.h"
#include "GoodnessFunction.h"
#include "TransformFunction.h"
#include "SRSUnitDisplayModes.h"
#include "OpenCVHelpers.h"
#include "BrainLocatable.h"
#include "BrainConnectable.h"
#include "Tickable.h"

namespace SRS22 {
	class ConceptMap : public BrainLocatable, public BrainConnectable, public Tickable
	{
	public:
		Brain* myBrain = NULL;

		std::string MapName;
		std::string MapDescription;

		const MapUidE UID;

		/// <summary>
		/// How the Monitor app should display this Concept Map.
		/// </summary>
		SRSUnitDisplayModes displayMode = SRSUnitDisplayModes::COLOR;

	private: 
		/// <summary>
		/// 0.0 is instant decay, 1.0 is infinitely slow decay. This is decay toward 0.0 per tick as a multiplicative factor.
		/// <para>In LatchNextState:</para>
		/// <code>M = M * decayFactor + nextM; 
		/// nextM = 0.0;</code>
		/// </summary>
		float decayFactor = 1.0f;

	public:

		PatternMatchingSystem matchSystem;
		std::shared_ptr<GoodnessFunction> goodnessFunc;

		ConceptState M;
		ConceptState nextM;

		const int Width() { if (M.charges.dims < 3) return M.charges.cols; else return M.charges.size[2]; }
		const int Height() { if (M.charges.dims < 3) return M.charges.rows; else return M.charges.size[1]; }
		const int Depth() { if (M.charges.dims < 3) return 1; else return M.charges.size[0]; }
		const int CVType() { return M.charges.type(); }
		const std::string CVTypeString() { return OpenCVHelpers::CVTypeToStr(M.charges.type()); }

		/// <summary>
		/// The MapName is almost always the class name of the sub-class, e.g. "ScreenFoveaMap".
		/// In the case of cortex maps it may not be the class name.
		/// </summary>
		/// <param name="MapName"></param>
		/// <param name="UID">Must be globally unique. See MapUIDs.h</param>
		/// <param name="ctrip"></param>
		/// <param name="location"></param>
		/// <param name="cols"></param>
		/// <param name="decayFactor">0.0 means instant decay to zero before every tick. 1.0 is infinite sustain.
		/// Done with multiplicative decay. In LatchNewState does <code>nextM = M * decayFactor; nextM = 0.0f;</code></param>
		/// <param name="MapDescription"></param>
		ConceptMap(Brain* br, MapUidE UID, bool isConnectable, std::string MapName, const cv::Vec3f location, int cols, float decayFactor, std::string MapDescription);
		ConceptMap(Brain* br, MapUidE UID, bool isConnectable, std::string MapName, const cv::Vec3f location, int rows, int cols, float decayFactor, std::string MapDescription);
		ConceptMap(Brain* br, MapUidE UID, bool isConnectable, std::string MapName, const cv::Vec3f location, int layers, int rows, int cols, float decayFactor, std::string MapDescription);

		~ConceptMap();

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
		/// Process all inputs and system state, compare patterns, do transforms.
		/// Do NOT change M, just add or subtract from nextM state. Gets called in parallel for all SRSUnits.
		/// </summary>
		virtual void ComputeNextState() override;

		/// <summary>
		/// After processIO has been called on all SRSUnits, this gets called to decay M and then add the nextM state to M.
		/// Gets called in parallel for all SRSUnits. So must be just state transfer inside the ConceptMap.
		/// This is NOT the place to do any post processing on the next state!
		/// </summary>
		virtual void LatchNewState() override;

		virtual std::string Debug();

		int GetRandomLinearOffset() override;
		void GenerateNearFarLists() {};

		float GetChargeValue(const int linearOffset) override;
		void SetChargeValue(const int linearOffset, const float c) override;
		void AddToChargeValue(const int linearOffset, const float c) override;

	};
}
