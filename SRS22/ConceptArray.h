#pragma once

#include "ArrayUIDs.h"
#include "Brain.h"
#include "GoodnessFunction.h"
#include "SRSUnitDisplayModes.h"
#include "Tickable.h"
#include <opencv2/core/mat.hpp>
#include <string>

namespace SRS22 {
	class ConceptArray : public Tickable
	{
	public:
		Brain* myBrain = NULL;

		std::string ArrayName;
		std::string ArrayDescription;
		const int cols;
		const int rows;
		const int depth;
		/// <summary>
		/// cols * rows * depth
		/// </summary>
		const int totalSize;
		const int rowsXcols;

		/// <summary>
		/// For easy use with cv::Mat. { depth, rows, cols }
		/// </summary>
		int dims[3];

		NeuronType neuronType = NeuronType::REGULAR;

		/// <summary>
		/// The cortex segment allocated to this array extends from cortexStartIndex to cortexStartIndex + totalSize.
		/// </summary>
		int cortexStartIndex = -1;

		/// <summary>
		/// A cv::Mat with the actual memory backed by the Cortex.neuronCharges array segment.
		/// NEVER change this cv::Mat. It is just a mirror of the Cortex.neuronCharges array segment.
		/// </summary>
		cv::Mat M;
		/// <summary>
		/// A cv::Mat with the actual memory backed by the Cortex.neuronChargesNext array segment.
		/// NEVER change this cv::Mat (except for I/O input). It is just a mirror of the Cortex.neuronChargesNext array segment.
		/// </summary>
		cv::Mat nextM;

		const ArrayUidE UID;

		/// <summary>
		/// How the Monitor app should display this  Concept Array.
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

		std::shared_ptr<GoodnessFunction> goodnessFunc;

		const int Width() const { return cols; }
		const int Cols() const { return cols; }
		const int Height() const { return rows; }
		const int Rows() const { return rows; }
		const int Depth() const { return depth; }

		/// <summary>
		/// The ArrayName is almost always the class name of the sub-class, e.g. "ScreenFoveaArray".
		/// In the case of cortex arrays it may not be the class name.
		/// </summary>
		/// <param name="br">The brain that owns this array. Future feature: Allow  a world with multiple brains.</param>
		/// <param name="UID">Must be globally unique. See ArrayUIDs.h</param>
		/// <param name="ArrayName"></param>
		/// <param name="computeNextStateEnabled">Default is true. If the array is in I/O input array then this is false. 
		/// See NeuronType.PERMANENT_DISABLED</param>
		/// <param name="cols"></param>
		/// <param name="decayFactor">0.0 means instant decay to zero before every tick. 1.0 is infinite sustain.
		/// Done with multiplicative decay. In LatchNewState does <code>nextM = M * decayFactor; nextM = 0.0f;</code></param>
		/// <param name="ArrayDescription"></param>
		ConceptArray(Brain* br, ArrayUidE UID, std::string ArrayName, NeuronType neuronType, int cols, float decayFactor, std::string ArrayDescription);
		ConceptArray(Brain* br, ArrayUidE UID, std::string ArrayName, NeuronType neuronType, int rows, int cols, float decayFactor, std::string ArrayDescription);
		ConceptArray(Brain* br, ArrayUidE UID, std::string ArrayName, NeuronType neuronType, int depth, int rows, int cols, float decayFactor, std::string ArrayDescription);

		~ConceptArray();

		/// <summary>
		/// Copy current charge to next charge.
		/// </summary>
		void CopyToNext();

		void put(int idx, float val);
		float get(int idx);
		void put(int row, int col, float val);
		float get(int row, int col);
		void put(int depth, int row, int col, float val);
		float get(int depth, int row, int col);

		void putNext(int idx, float val);
		float getNext(int idx);
		void putNext(int row, int col, float val);
		float getNext(int row, int col);
		void putNext(int depth, int row, int col, float val);
		float getNext(int depth, int row, int col);

		void add(int idx, float val);
		void add(int row, int col, float val);
		void add(int depth, int row, int col, float val);

		void addNext(int idx, float val);
		void addNext(int row, int col, float val);
		void addNext(int depth, int row, int col, float val);

		void sub(int idx, float val);
		void sub(int row, int col, float val);
		void sub(int depth, int row, int col, float val);

		void subNext(int idx, float val);
		void subNext(int row, int col, float val);
		void subNext(int depth, int row, int col, float val);

		void mul(int idx, float val);
		void mul(int row, int col, float val);
		void mul(int depth, int row, int col, float val);

		void mulNext(int idx, float val);
		void mulNext(int row, int col, float val);
		void mulNext(int depth, int row, int col, float val);

		void div(int idx, float val);
		void div(int row, int col, float val);
		void div(int depth, int row, int col, float val);

		void divNext(int idx, float val);
		void divNext(int row, int col, float val);
		void divNext(int depth, int row, int col, float val);

		/// <summary>
		/// Ends in two 'p' s to avoid conflict with the C++ keyword 'clamp'.
		/// </summary>
		void clampp(int idx, float min = -1.0f, float max = 1.0f);
		void clampp(int row, int col, float min = -1.0f, float max = 1.0f);
		void clampp(int depth, int row, int col, float min = -1.0f, float max = 1.0f);

		void clampNext(int idx, float min = -1.0f, float max = 1.0f);
		void clampNext(int row, int col, float min = -1.0f, float max = 1.0f);
		void clampNext(int depth, int row, int col, float min = -1.0f, float max = 1.0f);

		/// <summary>
		/// Relax M toward zero into nextM by factor. 1.0 is no relaxation, 0.0 is instant relaxation.
		/// </summary>
		/// <param name="factor"></param>
		void RelaxTowardZero(float factor) {
			nextM = M * factor;
		}

		/// <summary>
		/// Find the maximum value in M and return the row, col, depth and value.
		/// But not less than minV. If no value is greater than minV returns false.
		/// If return is false, col, row, depth, v are indeterminant.
		/// </summary>
		/// <param name="idx"></param>
		/// <param name="min"></param>
		/// <param name="max"></param>
		bool FindMaxValue(const float minV, OUT int& col, OUT int& row, OUT int& depth, OUT float& v);

		/// <summary>
		/// Create cv::Mat M and nextM such that they point at the memory from the Cortex.neuronCharges array
		/// and do not free the memory when destroyed. Thus they are "header only" cv::Mats.
		/// </summary>
		void setupCVMatMirrors();

		/// <summary>
		/// Called after all SRSUnits have been created and added to the Brain.
		/// </summary>
		void PostCreate(Brain& b);

		/// <summary>
		/// Process all inputs and system state, compare patterns, do transforms.
		/// Do NOT change M, just add or subtract from nextM state. Gets called in parallel for all SRSUnits.
		/// </summary>
		virtual void ComputeNextState(boolean doParallel) override;

		/// <summary>
		/// After processIO has been called on all SRSUnits, this gets called to decay M and then add the nextM state to M.
		/// Gets called in parallel for all SRSUnits. So must be just state transfer inside the ConceptArray.
		/// This is NOT the place to do any post processing on the next state!
		/// </summary>
		virtual void LatchNewState(boolean doParallel) override;

		virtual std::string Debug();
	};

	typedef std::shared_ptr<ConceptArray> ConceptArrayH;
}
