#pragma once
#include <cstdint>
#include <chrono>

namespace profiler {

    class Clock {
    public:
        /**
         * @brief Returns a monotonic timestamp in microseconds.
         *
         * Uses steady_clock to avoid time jumps.
         * time_since_epoch is consistent across translation units.
         */
        static uint64_t now_us() noexcept {
            using clock = std::chrono::steady_clock;
            return static_cast<uint64_t>(
                std::chrono::duration_cast<std::chrono::microseconds>(
                    clock::now().time_since_epoch()
                ).count()
                );
        }
    };

} // namespace profiler
