#pragma once
#include "Rect.h"

namespace SRS22 {

	class OpenCVHelpers {
	public:
		static std::string CVTypeToStr(const int type);

		/// <summary>
		/// Some debug info.
		/// </summary>
		/// <param name="m"></param>
		/// <returns></returns>
		static std::string CVMatrixInfo(cv::Mat& m);

		/// <summary>
		/// Get a matrix of a subrect in inputMat. So far is coded for CV_32FC1 either 1 or 3 layers.
		/// Assumes inputMat is an RGB image CV_3UC8. From camera or screen etc. If outM is 3 layer then converts 
		/// 0 to 255 pixels to 0.0 to 1.0 values in the 3 layers. If outM is 1 layer, converts to grey.
		/// If inputMatRGB is empty then does nothing.
		/// </summary>
		/// <param name="inputMat"></param>
		/// <param name="outM"></param>
		/// <param name="region"></param>
		static void CVGetSubRectRGB(cv::Mat& inputMatRGB, cv::Mat& outM, const SRS22::Rect& region);

		/// <summary>
		/// A straight conversion copy from 3UC8 to 3 planes F32.
		/// If inputMatRGB is empty then does nothing.
		/// </summary>
		/// <param name="inputMatRGB"></param>
		/// <param name="outM"></param>
		static void CVCopyRGBToMat(cv::Mat& inputMatRGB, cv::Mat& outM);

		/// <summary>
		/// Gets width of matrix regardless of whether it is empty, 2D or multi D.
		/// </summary>
		/// <param name="m"></param>
		static int CVMatrixCols(const cv::Mat& m);
		static int CVMatrixRows(const cv::Mat& m);
		/// <summary>
		/// If 3D then the Z dimension. All others are 0 for empty() else 1.
		/// </summary>
		/// <param name="m"></param>
		/// <returns></returns>
		static int CVMatrixPlanes(const cv::Mat& m);
	};
}