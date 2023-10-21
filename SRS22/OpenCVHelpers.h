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
		static std::string CVMatrixInfo(const cv::Mat& m);

		static std::string MapUIText(cv::Mat& m);

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

		/// <summary>
		/// Assumes the m is CV_32FC1. Like camera shots as float range 0.0 to 1.0.
		/// Assumes m0, m1, m2 will be 2D matrices with rows equal to m.size[1] and cols equal to m.size[2].
		/// 
		/// Asserts 
		/// <code>
		/// assert(m.type() == CV_32FC3);
		/// assert(m0.type() == CV_32FC1);
		/// assert(m1.type() == CV_32FC1);
		/// assert(m2.type() == CV_32FC1);
		/// 
		/// assert(m.rows == -1);
		/// assert(m.cols == -1);
		/// assert(m.size.dims() == 3);
		/// assert(m0.rows == m.size[2]);
		/// assert(m0.cols == m.size[1]);
		/// assert(m1.rows == m.size[2]);
		/// assert(m1.cols == m.size[1]);
		/// assert(m2.rows == m.size[2]);
		/// assert(m2.cols == m.size[1]);
		/// </code>
		/// </summary>
		static void ExtractPlanes32FC1_3PlaneTo32FC1x3(const cv::Mat& m, cv::Mat& m0, cv::Mat& m1, cv::Mat& m2);
		static void CombinePlanes32FC1x3to32FC1_3Plane(const cv::Mat& m0, const cv::Mat& m1, const cv::Mat& m2, cv::Mat& m);
		/// <summary>
		/// Assumes m1, m2, m3 are RGB 0 to 255 values, CV_8UC1 Matrices.
		/// Assumes m0, m1, m2 are 2D so rows and cols are valid.
		/// </summary>
		/// <param name="m0"></param>
		/// <param name="m1"></param>
		/// <param name="m2"></param>
		/// <param name="m"></param>
		static void Combine8UC1x3To32FC1_3Plane(const cv::Mat& m0, const cv::Mat& m1, const cv::Mat& m2, cv::Mat& m);

		static bool is_file_path_writable(const std::filesystem::path& file_path);
		static void write_string_to_file(const std::filesystem::path& file_path, const std::string& file_contents);
		/// <summary>
		/// So far supports 3D 32FC1 x 3, or 8UC3 x1 images.
		/// </summary>
		/// <param name="output_file_path"></param>
		/// <param name="mat"></param>
		/// <param name="file_contents"></param>
		/// <param name="doFileDump"></param>
		/// <param name="doImShow"></param>
		static void error_aware_imwrite_imshow(const std::filesystem::path& output_file_path, const cv::Mat& mat, bool doFileDump = false, bool doImShow = false);
		/// <summary>
		/// mat8UC3 must be a 2D image with cv::Vec3b pixels.
		/// </summary>
		static void error_aware_imwrite_8UC3(const std::filesystem::path& output_file_path, const cv::Mat& mat8UC3);

		static void Convert32FC1To8UC1(cv::Mat& in, cv::Mat& out)
		{
			in.convertTo(out, CV_8U, 255.0);
		}
	};
}