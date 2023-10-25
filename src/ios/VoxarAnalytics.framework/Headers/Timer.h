#pragma once

#include <chrono>

namespace vxa
{
	namespace Timer
	{
		typedef std::chrono::steady_clock::time_point Instant;

        void init(Instant &timer);

        long long elapsed(Instant &begin_timer);

        long long time_milliseconds();
	}
}
