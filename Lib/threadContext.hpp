#pragma once
#include <cstdint>

namespace profiler{
	class ThreadContext {
	public:
		static uint32_t thread_id() noexcept;
	};
}