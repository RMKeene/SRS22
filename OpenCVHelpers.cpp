#include "OpenCVHelpers.h"
#include "Rect.h"

namespace SRS22 {
	using namespace std;
	string OpenCVHelpers::CVTypeToStr(const int type) {
		string r;

		uchar depth = type & CV_MAT_DEPTH_MASK;
		uchar chans = 1 + (type >> CV_CN_SHIFT);

		switch (depth) {
		case CV_8U:  r = "8U"; break;
		case CV_8S:  r = "8S"; break;
		case CV_16U: r = "16U"; break;
		case CV_16S: r = "16S"; break;
		case CV_32S: r = "32S"; break;
		case CV_32F: r = "32F"; break;
		case CV_64F: r = "64F"; break;
		default:     r = "User"; break;
		}

		r += "C";
		r += (chans + '0');

		return r;
	}

	std::string OpenCVHelpers::CVMatrixInfo(cv::Mat& m) {

		string r = CVTypeToStr(m.type());
		r += " : dims=";
		r += to_string(m.dims);
		if (m.dims >= 3) {
			r += " sizes ";
			for (int i = 0; i < m.dims; i++) {
				r += "size[" + to_string(i) + "]=" + to_string(m.size[i]) + " ";
			}
		}
		else {
			r += " rows=" + to_string(m.rows) + " cols=" + to_string(m.cols);
		}

		return r;
	}

	std::string OpenCVHelpers::MapUIText(cv::Mat& m) {
		int maxN = 20;
		std::string briefData = "";

		if (m.empty()) {
			briefData = "(empty)";
		}
		else if (m.cols > 0) { // 2D Matrix with 1 or 3 channels.
			std::string ty = CVTypeToStr(m.type());
			if (ty == "8UC1") {
				for (int r = 0; r < m.rows; r++) {
					for (int c = 0; c < m.cols; c++) {
						briefData += (int)m.at<unsigned char>(r, c);
						briefData += ", ";
						maxN--;
						if (maxN <= 0) break;
					}
					if (maxN <= 0) break;
					briefData += "\n";
				}
			}
			if (ty == "8UC3") {
				for (int r = 0; r < m.rows; r++) {
					for (int c = 0; c < m.cols; c++) {
						cv::Vec3b v = m.at<cv::Vec3b>(r, c);
						briefData += "[" + std::to_string((int)v[0]) + ", " + std::to_string((int)v[1]) + ", " + std::to_string((int)v[2]) + "] ";
						maxN--;
						if (maxN <= 0) break;
					}
					if (maxN <= 0) break;
					briefData += "\n";
				}
			}
			if (ty == "32FC1") {
				for (int r = 0; r < m.rows; r++) {
					for (int c = 0; c < m.cols; c++) {
						briefData += std::to_string(m.at<float>(r, c));
						briefData += "\n";
						maxN--;
						if (maxN <= 0) break;
					}
					if (maxN <= 0) break;
					briefData += "\n";
				}
			}

			if (ty == "32FC3") {
				for (int r = 0; r < m.rows; r++) {
					for (int c = 0; c < m.cols; c++) {
						cv::Vec3f v = m.at<cv::Vec3f>(r, c);
						briefData += "[" + std::to_string(v[0]) + ", " + std::to_string(v[1]) + ", " + std::to_string(v[2]) + "] ";
						maxN--;
						if (maxN <= 0) break;
					}
					if (maxN <= 0) break;
					briefData += "\n";
				}
			}
			briefData += "...";
		}
		else if (m.size.dims() == 3) { // 3D Matrix, not channels.

			for (int z = 0; z < m.size[0]; z++) {
				for (int y = 0; y < m.size[1]; y++) {
					for (int x = 0; x < m.size[2]; x++) {
						briefData += std::to_string(m.at<float>(z, y, x));
						briefData += ", ";
						if (maxN <= 0) break;
					}
					if (maxN <= 0) break;
					briefData += "\n";
				}
				if (maxN <= 0) break;
				briefData += "\n";
				briefData += "\n";
			}
		}
		else {
			briefData += "Unknown Matrix Layout.";
		}

		return CVMatrixInfo(m) + std::string(" : ") + briefData;
	}

	void OpenCVHelpers::CVGetSubRectRGB(cv::Mat& inputMatRGB, cv::Mat& outM, const SRS22::Rect& region) {
		if (inputMatRGB.empty())
			return;

		if (outM.type() == CV_32FC1) {
			if (outM.dims == 3) {
				if (outM.size[0] == 3) {
					for (int y = region.top(); y < region.bottom(); y++) {
						const int yy = y - region.Y;
						if (yy >= 0 && yy < outM.size[1] && y >= 0 && y < inputMatRGB.rows) {
							for (int x = region.left(); x < region.right(); x++) {
								const int xx = x - region.X;
								if (xx >= 0 && xx < outM.size[2] && x >= 0 && x < inputMatRGB.cols) {
									if (inputMatRGB.type() == CV_8UC4) {
										const cv::Vec4b& n = inputMatRGB.at<cv::Vec4b>(y, x);
										outM.at<float>(0, yy, xx) = n[0] / 255.0f;
										outM.at<float>(1, yy, xx) = n[1] / 255.0f;
										outM.at<float>(2, yy, xx) = n[2] / 255.0f;
									}
									else { // CV_8UC3 BGR
										const cv::Vec3b& n = inputMatRGB.at<cv::Vec3b>(y, x);
										outM.at<float>(0, yy, xx) = n[2] / 255.0f;
										outM.at<float>(1, yy, xx) = n[1] / 255.0f;
										outM.at<float>(2, yy, xx) = n[0] / 255.0f;
									}
								}
							}
						}
					}
				}
				else if (outM.size[0] == 1) {
					for (int y = region.top(); y < region.bottom(); y++) {
						for (int x = region.left(); x < region.right(); x++) {
							const cv::Vec4b n = inputMatRGB.at<cv::Vec4b>(y, x);
							const float vv = (n[0] / 255.0f + n[1] / 255.0f + n[2] / 255.0f) / 3.0f;
							outM.at<float>(0, y, x) = vv;
						}
					}
				}
				else {
					throw std::logic_error("dims = 3, size[0] not 1 or 3 - TODO Implement this.");
				}
			}
			else {
				throw std::logic_error("Unimplemented GetSubRect out data type. dims != 3 - TODO Implement this.");
			}
		}
		else {
			throw std::logic_error("Unimplemented GetSubRect out data type. not type CV_32FC1. - TODO implement this.");
		}
	}

	void OpenCVHelpers::CVCopyRGBToMat(cv::Mat& inputMatRGB, cv::Mat& outM) {
		if (inputMatRGB.empty())
			return;
		CVGetSubRectRGB(inputMatRGB, outM,
			SRS22::Rect(0, 0, OpenCVHelpers::CVMatrixCols(inputMatRGB), OpenCVHelpers::CVMatrixRows(inputMatRGB)));
	}

	int OpenCVHelpers::CVMatrixCols(const cv::Mat& m) {
		if (m.empty())
			return 0;
		if (m.cols > 0)
			return m.cols;
		return m.size[m.dims - 1];
	}

	int OpenCVHelpers::CVMatrixRows(const cv::Mat& m) {
		if (m.empty())
			return 0;
		if (m.rows > 0)
			return m.rows;
		return m.size[m.dims - 2];
	}

	int OpenCVHelpers::CVMatrixPlanes(const cv::Mat& m) {
		if (m.empty())
			return 0;
		if (m.rows > 0)
			return 1;
		return m.size[m.dims - 3];
	}

}