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

	void OpenCVHelpers::CVGetSubRectRGB(cv::Mat& inputMatRGB, cv::Mat& outM, const SRS22::Rect& region) {
		if (outM.type() == CV_32FC1) {
			if (outM.dims == 3) {
				if (outM.size[0] == 3) {
					for (int y = region.top(); y < region.bottom(); y++) {
						const int yy = y - region.Y;
						for (int x = region.left(); x < region.right(); x++) {
							const int xx = x - region.X;
							if (inputMatRGB.type() == CV_8UC4) {
								const cv::Vec4b n = inputMatRGB.at<cv::Vec4b>(y, x);
								outM.at<float>(0, yy, xx) = n[0] / 255.0f;
								outM.at<float>(1, yy, xx) = n[1] / 255.0f;
								outM.at<float>(2, yy, xx) = n[2] / 255.0f;
							}
							else { // CV_8UC3 BGR
								const cv::Vec3b n = inputMatRGB.at<cv::Vec3b>(y, x);
								outM.at<float>(0, yy, xx) = n[2] / 255.0f;
								outM.at<float>(1, yy, xx) = n[1] / 255.0f;
								outM.at<float>(2, yy, xx) = n[0] / 255.0f;
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
}