#include "OpenCVHelpers.h"
#include "Rect.h"

namespace SRS22 {
	using namespace std;
	using namespace cv;

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

	std::string OpenCVHelpers::CVMatrixInfo(const cv::Mat& m) {
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

	bool OpenCVHelpers::is_file_path_writable(const std::filesystem::path& file_path)
	{
		const auto status = std::filesystem::status(file_path);
		const auto permissions = status.permissions();

		// Check if the file or directory is writable
		return (permissions & std::filesystem::perms::owner_write) != std::filesystem::perms::none ||
			(permissions & std::filesystem::perms::group_write) != std::filesystem::perms::none ||
			(permissions & std::filesystem::perms::others_write) != std::filesystem::perms::none;
	}

	void OpenCVHelpers::write_string_to_file(const std::filesystem::path& file_path, const std::string& file_contents)
	{
		std::ofstream file_writer;
		file_writer.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		file_writer.open(file_path.wstring(), std::ios::out | std::ios::binary);
		file_writer << file_contents;
	}

	void OpenCVHelpers::error_aware_imwrite_imshow(const std::filesystem::path& output_file_path, const cv::Mat& mat, bool doFileDump, bool doImShow)
	{
		if (mat.empty())
		{
			// No image.
			return;
		}

		// Convert to dims == 2 and CV_8UC3
		Mat rmat(mat.size[1], mat.size[2], CV_8UC3);
		if (mat.type() != CV_8UC3 && mat.dims == 2) {
			rmat = mat;
		}
		else if (mat.type() == CV_32FC1 && mat.cols == -1 && mat.rows == -1 && mat.size.dims() == 3) { // This matches the input camera and screen raw images and fovea.
			Mat temp;
			std::string im = CVMatrixInfo(mat);
			mat.convertTo(temp, CV_8UC1, 255.0);
			im = CVMatrixInfo(temp);
			// Convert from 3 z planes to 1 RGB plane so CV_8UC1 planes to CV8UC3 pixels.
			for (int y = 0; y < temp.size[1]; y++) {
				for (int x = 0; x < temp.size[2]; x++) {
					const Vec3b n = Vec3b(temp.at<uchar>(0, y, x), temp.at<uchar>(1, y, x), temp.at<uchar>(2, y, x));
					rmat.at<Vec3b>(y, x) = n;
				}
			}
			im = CVMatrixInfo(rmat);
		}
		else {
			throw std::logic_error("Unsupported matrix type to save to disk or show. " + CVMatrixInfo(mat));
		}

		if (doFileDump) {
			error_aware_imwrite_8UC3(output_file_path, rmat);
		}

		if (doImShow) {
			imshow(output_file_path.string(), rmat);
		}
	}

	void OpenCVHelpers::error_aware_imwrite_8UC3(const std::filesystem::path& output_file_path, const cv::Mat& mat8UC3) {
		if (const auto parent_path = output_file_path.parent_path();
			!is_directory(parent_path))
		{
			throw std::runtime_error("Parent directory did not exist: " + parent_path.string());
		}

		if (is_regular_file(output_file_path) && !is_file_path_writable(output_file_path))
		{
			throw std::runtime_error("File path is not writable");
		}

		const auto file_extension = output_file_path.extension().string();

		std::vector<uchar> buffer;
#define MB ((size_t)1024*1024)
		buffer.resize(10 * MB);

		//Mat rmat = imread("E:\\TruGolfTestData\\3DRenderedShots\\AP_1616_0\\Cam0_8.jpg");

		if (const auto successfully_encoded = imencode(file_extension, mat8UC3, buffer);
			!successfully_encoded)
		{
			throw std::runtime_error("Imagine encoding failed");
		}

		// Write to the file
		const auto written_file_contents = std::string(buffer.begin(), buffer.end());
		if (written_file_contents.empty())
		{
			throw std::runtime_error("Written image bytes were empty");
		}

		write_string_to_file(output_file_path, written_file_contents);
	}

	void OpenCVHelpers::ExtractPlanes32FC1(const cv::Mat& m, cv::Mat& m0, cv::Mat& m1, cv::Mat& m2) {
		if (m.empty())
			return;

		assert(m.type() == CV_32FC1);
		assert(m0.type() == CV_32FC1);
		assert(m1.type() == CV_32FC1);
		assert(m2.type() == CV_32FC1);

		assert(m.rows == -1);
		assert(m.cols == -1);
		assert(m.size.dims() == 3);
		assert(m0.rows == m.size[2]);
		assert(m0.cols == m.size[1]);
		assert(m1.rows == m.size[2]);
		assert(m1.cols == m.size[1]);
		assert(m2.rows == m.size[2]);
		assert(m2.cols == m.size[1]);


		for (int y = 0; y < m.size[1]; y++) {
			for (int x = 0; x < m.size[2]; x++) {
				m0.at<float>(y, x) = m.at<float>(0, y, x);
				m1.at<float>(y, x) = m.at<float>(1, y, x);
				m2.at<float>(y, x) = m.at<float>(2, y, x);
			}
		}

	}

	void OpenCVHelpers::CombinePlanes32FC1(const cv::Mat& m0, const cv::Mat& m1, const cv::Mat& m2, cv::Mat& m) {
		if (m0.empty())
			return;

		assert(m.type() == CV_32FC1);
		assert(m0.type() == CV_32FC1);
		assert(m1.type() == CV_32FC1);
		assert(m2.type() == CV_32FC1);

		assert(m.rows == -1);
		assert(m.cols == -1);
		assert(m.size.dims() == 3);
		assert(m0.rows == m.size[2]);
		assert(m0.cols == m.size[1]);
		assert(m1.rows == m.size[2]);
		assert(m1.cols == m.size[1]);
		assert(m2.rows == m.size[2]);
		assert(m2.cols == m.size[1]);

		for (int y = 0; y < m0.size[0]; y++) {
			for (int x = 0; x < m0.size[1]; x++) {
				m.at<float>(0, y, x) = m0.at<float>(y, x);
				m.at<float>(1, y, x) = m1.at<float>(y, x);
				m.at<float>(2, y, x) = m2.at<float>(y, x);
			}
		}
	}
}