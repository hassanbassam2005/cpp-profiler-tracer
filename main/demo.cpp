#include <thread>
#include <chrono>
#include <iostream>

#include "profiler.hpp"
#include "macros.hpp"

static void worker() {
    PROFILE_FUNCTION();
    std::this_thread::sleep_for(std::chrono::milliseconds(30));

    {
        PROFILE_SCOPE("Worker::HeavyBlock");
        std::this_thread::sleep_for(std::chrono::milliseconds(60));
    }
}

int main() {
    profiler::Profiler::begin_session("demo", "trace.json");

    {
        PROFILE_SCOPE("Main::Startup");
        std::this_thread::sleep_for(std::chrono::milliseconds(40));
    }

    std::thread t(worker);

    {
        PROFILE_SCOPE("Main::Work");
        std::this_thread::sleep_for(std::chrono::milliseconds(80));
    }

    t.join();

    profiler::Profiler::end_session();

    std::cout << "Wrote trace.json\n";
    return 0;
}
