#pragma once
#include <vector>
#include <cstddef>
#include <cstdint>
#include "event.hpp"

namespace profiler {

    class TraceWriter;

    class ThreadBuffer {
    public:
        /**
         * @brief Returns this thread's buffer (allocated once per thread).
         *
         * Implementation uses thread_local pointer to keep it alive.
         */
        static ThreadBuffer& local() noexcept;

        /**
         * @brief Adds an event to the buffer. Drops if full.
         */
        void push(const Event& e) noexcept;

        /**
         * @brief Flushes events to the writer.
         */
        void flush_to(TraceWriter& w);

    private:
        ThreadBuffer();

        std::vector<Event> events_;
        size_t max_events_ = 4096;
        uint64_t dropped_ = 0;
    };

} // namespace profiler
