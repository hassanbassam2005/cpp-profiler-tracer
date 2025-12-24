#include "buffer.hpp"
#include "writer.hpp"
#include "profiler.hpp"

namespace profiler {

    ThreadBuffer::ThreadBuffer() {
        events_.reserve(max_events_);
    }

    ThreadBuffer& ThreadBuffer::local() noexcept {
        // Keep it alive until process end.
        // This avoids dangling pointers if threads exit before end_session.
        thread_local ThreadBuffer* buf = []() {
            auto* b = new ThreadBuffer();
            Profiler::register_buffer(b);
            return b;
            }();
        return *buf;
    }

    void ThreadBuffer::push(const Event& e) noexcept {
        if (events_.size() < max_events_) {
            events_.push_back(e);
        }
        else {
            ++dropped_;
        }
    }

    void ThreadBuffer::flush_to(TraceWriter& w) {
        for (const auto& e : events_) {
            w.write_event(e);
        }
        events_.clear();
    }

} // namespace profiler
