#pragma once
#include "pch.h"
#include "ClassPredefines.h"
#include "tinyfloat.h"

namespace SRS22 {

	class ConceptState
	{
	public:

		/// <summary>
		/// The charges of this ConceptState. 
		/// 
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

		virtual std::string Debug();
	};

}
