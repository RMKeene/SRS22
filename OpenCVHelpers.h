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
		/// Assumes inputMat is an RGB image. From camera or screen etc. If outM is 3 layer then converts 
		/// 0 to 255 pixels to 0.0 to 1.0 values in the 3 layers. If outM is 1 layer, converts to grey.
		/// </summary>
		/// <param name="inputMat"></param>
		/// <param name="outM"></param>
		/// <param name="region"></param>
		static void CVGetSubRectRGB(cv::Mat& inputMatRGB, cv::Mat& outM, const SRS22::Rect& region);

	};
}