#pragma once
#include "pch.h"
#include "ClassPredefines.h"
#include "tinyfloat.h"

namespace SRS22 {
	class ConceptState
	{
	public:
		/// <summary>
		/// The charges of this ConceptState. In general a charge is range 0.0f to 1.0f.
		/// Possibly can be a little outside of that range. Weights of connections can be positive or negative,
		/// thus we get stimulation and inhibition.
		/// </summary>
		const float MinCharge = 0.0f;
		const float MaxCharge = 1.0f;

		/// <summary>
		/// cv::Mat works with reverse order layers, rows, cols or Z, Y, X or depth, height, width.
		/// sv::Mat.size() return a 1 or 2 or 3 element array of axis sizes in the above orders.
		/// </summary>
		cv::Mat charges;

		ConceptState(int cols);
		ConceptState(int rows, int cols);
		ConceptState(int layers, int rows, int cols);
		~ConceptState();

		float get(int col);
		float get(int row, int col);
		float get(int layer, int row, int col);
		void put(float v, int col);
		void put(float v, int row, int col);
		void put(float v, int layer, int row, int col);

		/// <summary>
		/// The cv::Mat size() function. 
		/// </summary>
		/// <returns></returns>
		const cv::MatSize matSize();

		// How many dimensions there are. E.g. 1 is 1D, 2 is a 2D matrix etx. Max is 3.
		const int dimensionCount();

		/// <summary>
		/// The total number of elements in this map. rows * cols * layers
		/// </summary>
		/// <returns></returns>
		const int entriesCount();

		/// <summary>
		/// The total number of bytes in this map. rows * cols * layers * sizeof(float)
		/// </summary>
		/// <returns></returns>
		const int byteCount();

		/// <summary>
		/// Element by element equality. this and other must be the same size. skip is ignored for now.
		/// Will throw if sizes missmatch.
		/// </summary>
		/// <param name="other"></param>
		/// <param name="skip"></param>
		/// <returns></returns>
		float Compare(std::shared_ptr<ConceptState> other, const int skip = 1);

		static void Copy(ConceptState& fromM, ConceptState& toM);

		/// <summary>
		/// Decay all charges toward V. Each time tick V += (chargeValue - V) * relaxationRate;
		/// </summary>
		/// <param name="V"></param>
		/// <param name="relaxationRate"></param>
		void RelaxTowardValue(const float V, const float relaxationRate = 1.0f);

		/// <summary>
		/// Find the maximum value in the State array. all parameters are out variables.
		/// minV is the minimum value to return true. The beginning minimum value is std::numeric_limits<float>::lowest()
		/// which is -(FLT_MAX) representing a hard low limit on minV.
		/// </summary>
		/// <param name="col"></param>
		/// <param name="row"></param>
		/// <param name="depth"></param>
		/// <param name="v"></param>
		/// <returns></returns>
		bool FindMaxValue(const float minV, OUT int& col, OUT int& row, OUT int& depth, OUT float& v);

		virtual std::string Debug();
	};
}
