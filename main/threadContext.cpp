#include "threadContext.hpp"

#ifdef _WIN32
#define NOMINMAX
#include<Windows.h>
#endif
#include <thread>

namespace profiler {
	uint32_t ThreadContext::thread_id() noexcept {
#ifdef _WIN32
		return static_cast<uint32_t>(::GetCurrentThreadId());
#else
		static_assert(sizeof(std::thread::id) >= sizeof(uint32_t), "Unexpected thread::id size.");
		return static_cast<uint32_t>(std::hash<std::thread>{}(std::this_thread::get_id()));
#endif 

	}
}