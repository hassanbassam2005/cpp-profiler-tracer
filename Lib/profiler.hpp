#pragma once
#include <atomic>
#include <mutex>
#include <vector>
#include "event.hpp"

namespace profiler {

    class ThreadBuffer;

    class Profiler {
    public:
        /**
         * @brief Starts a profiling session and opens the output trace file.
         *
         * Call this once near program start.
         */
        static void begin_session(const char* session_name, const char* path);

        /**
         * @brief Ends the session, flushes buffers, and closes the output file.
         *
         * Important: call after worker threads are joined for clean traces.
         */
        static void end_session();

        /**
         * @brief Records a Begin event for a named scope.
         */
        static void record_begin(const char* name) noexcept;

        /**
         * @brief Records an End event for a named scope.
         */
        static void record_end(const char* name) noexcept;

        /**
         * @brief Returns true if recording is active.
         */
        static bool is_active() noexcept;

        /**
         * @brief Internal: registers a thread buffer for flushing.
         */
        static void register_buffer(ThreadBuffer* b);

    private:
        Profiler() = delete;
    };

} // namespace profiler
