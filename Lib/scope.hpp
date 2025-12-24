#pragma once
#include "profiler.hpp"

namespace profiler {

    class Scope {
    public:
        /**
         * @brief Begins a named profiling scope.
         */
        explicit Scope(const char* name) noexcept : name_(name) {
            Profiler::record_begin(name_);
        }

        /**
         * @brief Ends the profiling scope automatically.
         */
        ~Scope() noexcept {
            Profiler::record_end(name_);
        }

        Scope(const Scope&) = delete;
        Scope& operator=(const Scope&) = delete;

    private:
        const char* name_;
    };

} // namespace profiler
