#include "OpenCVHelpers.h"

namespace SRS22 {
    using namespace std;
    string CVTypeToStr(const int type) {
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

    std::string CVMatrixInfo(cv::Mat& m) {

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
}