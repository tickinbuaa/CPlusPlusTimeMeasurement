//
// Created by 胡磊 on 2021/5/7.
//
#include <vector>
#include <ostream>
#include <iostream>
#include "PerformanceRecorder.hpp"
#include "PerformanceRecordTimer.hpp"

PerformanceRecorder g_performance_recorder;

void PerformanceRecorder::clear() { records.empty(); }

// Print formatted statistics into output_stream.
void PerformanceRecorder::print(std::ostream &output_stream) {
    std::vector<PerformanceRecord> sorted_by_wall_time;
    records_map::iterator iter = records.begin();
    while (iter != records.end()) {
        sorted_by_wall_time.emplace_back(iter->second);
        iter++;
    }
    // Sort by wall clock time in descender order.
    std::sort(
            sorted_by_wall_time.begin(),
            sorted_by_wall_time.end(),
            [](PerformanceRecord &first, PerformanceRecord &second) {
                return first.wall_clock_counter > second.wall_clock_counter;
            });
    std::vector<PerformanceRecord>::iterator viter = sorted_by_wall_time.begin();
    while (viter != sorted_by_wall_time.end()) {
        PerformanceRecord &performance_record = *(viter++);
        output_stream << "["
                      << performance_record.file << ":"
                      << performance_record.line_number << "]"
                      << performance_record.name << ": wall clock time["
                      << performance_record.wall_clock_counter / PerformanceRecordTimer::get_counter_per_ms()
                      << "ms], invocation count[" << performance_record.count << "].\n";
    }
    output_stream.flush();
}