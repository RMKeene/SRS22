#pragma once

namespace SRS22 {

    std::string CVTypeToStr(const int type);

    /// <summary>
    /// Some debug info.
    /// </summary>
    /// <param name="m"></param>
    /// <returns></returns>
    std::string CVMatrixInfo(cv::Mat& m);
}