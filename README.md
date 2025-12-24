# cpp-trace-profiler

A lightweight **C++ instrumentation profiler** that exports **Chrome Trace** (`trace.json`) timelines.
Mark scopes/functions in your code and inspect performance in `chrome://tracing`.

## Features
- Scope timing via RAII (`PROFILE_SCOPE`)
- Function profiling (`PROFILE_FUNCTION`)
- Multi-thread aware (thread ID lanes)
- Exports Chrome Trace JSON (`trace.json`)
- Compile-time enable/disable switch

## Why?
Because guessing performance is expensive.
This tool turns “it feels slow” into “this exact block costs 61 ms”.

## Quick Start

### 1) Add the library
You can vendor the code:
- Copy `include/` and `src/` into your project
- Or add as a submodule

### 2) Include and start a session
```cpp
#include "profiler/profiler.hpp"
#include "profiler/macros.hpp"

int main() {
    profiler::Profiler::begin_session("demo", "trace.json");

    {
        PROFILE_SCOPE("Main::Startup");
        // work...
    }

    profiler::Profiler::end_session();
}
