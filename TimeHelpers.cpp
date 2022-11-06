#include "TimeHelpers.h"

namespace SRS22 {
	long long GetTimeTicksSeconds() {
		auto now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::seconds>(duration).count();
		return millis;
	}

	long long GetTimeTicksMs() {
		auto now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::milliseconds>(duration).count();
		return millis;
	}

	long long GetTimeTicksUs() {
		auto now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
		return millis;
	}

	long long GetTimeTicksNs() {
		auto now = std::chrono::system_clock::now();
		auto duration = now.time_since_epoch();
		auto millis = std::chrono::duration_cast<std::chrono::nanoseconds>(duration).count();
		return millis;
	}
}