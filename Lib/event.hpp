#pragma once

#include <cstdint>

namespace profiler {
    enum class EventType : uint8_t {
        Begin = 0,
        End = 1
    };

    struct Event {
        uint64_t    ts_us;  // timestamp (microseconds)
        uint32_t    tid;    // thread id
        const char* name;   // event name (must stay valid)
        EventType   type;   // Begin / End
    };
}