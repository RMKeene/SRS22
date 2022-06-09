#include "TimeHelpers.h"

namespace SRS22 {

	std::chrono::milliseconds GetTimeTicksMs_ms{ 1 };

	long long GetTimeTicksMs() {
		auto now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		return millis;
	}

}