#include "writer.hpp"

namespace profiler {
	bool TraceWriter::open(const char* path) {
        out_.open(path, std::ios::out | std::ios::trunc);
        if (!out_.is_open()) return false;

        first_ = true;
        out_ << "{\"traceEvents\":[\n";
        return true;
	}

    void TraceWriter::write_escaped_json_string(std::ofstream& out, const char* s) {
        if (!s) { out << ""; return; }
        for (const char* p = s; *p; ++p) {
            const char c = *p;
            switch (c) {
            case '\\': out << "\\\\"; break;
            case '"':  out << "\\\""; break;
            case '\n': out << "\\n";  break;
            case '\r': out << "\\r";  break;
            case '\t': out << "\\t";  break;
            default:   out << c;      break;
            }
        }
    }

    void TraceWriter::write_event(const Event& e) {
        if (!out_.is_open()) return;

        if (!first_) out_ << ",\n";
        first_ = false;

        const char ph = (e.type == EventType::Begin) ? 'B' : 'E';

        out_ << "{"
            << "\"name\":\"";
        write_escaped_json_string(out_, e.name);
        out_ << "\","
            << "\"ph\":\"" << ph << "\","
            << "\"ts\":" << e.ts_us << ","
            << "\"pid\":0,"
            << "\"tid\":" << e.tid
            << "}";
    }

    void TraceWriter::close() {
        if (!out_.is_open()) return;
        out_ << "\n]}\n";
        out_.close();
    }
}