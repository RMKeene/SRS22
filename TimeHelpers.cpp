#include "TimeHelpers.h"

namespace SRS22 {

	long long GetTimeTicksMs() {
		long long timeTicks = std::chrono::system_clock::now().time_since_epoch().count();
		return timeTicks;
	}

}