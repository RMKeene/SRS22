#pragma once
#include "SRSUnit.h"

namespace SRS22 {
	class ScreenIn : public SRSUnit
	{
	public:
		ScreenIn(ConnectivityTriple ctrip, cv::Vec3f location, int w);
		ScreenIn(ConnectivityTriple ctrip, cv::Vec3f location, int w, int h);
		ScreenIn(ConnectivityTriple ctrip, cv::Vec3f location, int w, int h, int d);
		~ScreenIn();
	};

}
