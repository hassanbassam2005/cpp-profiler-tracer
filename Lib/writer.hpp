#pragma once
#include <cstddef>
#include <cstdint>
#include <fstream>
#include <string>
#include "event.hpp"

namespace profiler {
	class TraceWriter {
	public:
		TraceWriter() = default;
		TraceWriter(const TraceWriter&) = delete;
		TraceWriter& operator=(const TraceWriter&) = delete;
		bool open(const char* path);
		void write_event(const Event& e);
		void close();
		bool is_open() const noexcept { return out_.is_open(); }
	private:
		std::ofstream out_;
		bool first_ = true;

		static void write_escaped_json_string(std::ofstream& out, const char* s);
	};
}