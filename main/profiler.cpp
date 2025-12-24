#include "profiler.hpp"
#include "clock.hpp"
#include "threadContext.hpp"
#include "writer.hpp"
#include "buffer.hpp"

namespace profiler {

    struct ProfilerState {
        std::atomic<bool> active{ false };
        std::mutex mtx;
        std::vector<ThreadBuffer*> buffers;
        TraceWriter writer;
    };

    static ProfilerState& S() {
        static ProfilerState s;
        return s;
    }

    void Profiler::begin_session(const char* /*session_name*/, const char* path) {
        auto& s = S();
        std::lock_guard<std::mutex> lock(s.mtx);

        if (s.active.load(std::memory_order_relaxed)) {
            // If already active, end then restart. Simple and safe.
            s.active.store(false, std::memory_order_relaxed);
            s.writer.close();
        }

        if (!s.writer.open(path)) {
            s.active.store(false, std::memory_order_relaxed);
            return;
        }

        s.active.store(true, std::memory_order_release);
    }

    void Profiler::end_session() {
        auto& s = S();

        // Stop recording first.
        s.active.store(false, std::memory_order_release);

        std::lock_guard<std::mutex> lock(s.mtx);
        if (!s.writer.is_open()) return;

        for (ThreadBuffer* b : s.buffers) {
            if (b) b->flush_to(s.writer);
        }

        s.writer.close();
    }

    bool Profiler::is_active() noexcept {
        return S().active.load(std::memory_order_acquire);
    }

    void Profiler::register_buffer(ThreadBuffer* b) {
        auto& s = S();
        std::lock_guard<std::mutex> lock(s.mtx);
        s.buffers.push_back(b);
    }

    void Profiler::record_begin(const char* name) noexcept {
        if (!is_active()) return;

        Event e;
        e.ts_us = Clock::now_us();
        e.tid = ThreadContext::thread_id();
        e.name = name;
        e.type = EventType::Begin;

        ThreadBuffer::local().push(e);
    }

    void Profiler::record_end(const char* name) noexcept {
        if (!is_active()) return;

        Event e;
        e.ts_us = Clock::now_us();
        e.tid = ThreadContext::thread_id();
        e.name = name;
        e.type = EventType::End;

        ThreadBuffer::local().push(e);
    }

} // namespace profiler
