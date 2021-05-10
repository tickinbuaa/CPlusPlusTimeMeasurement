//
// Created by 胡磊 on 2021/5/7.
//

#ifndef C__TEST_PERFORMANCERECORDER_HPP
#define C__TEST_PERFORMANCERECORDER_HPP

#include <cstdint>
#include <string>
#include <map>
#include "PerformanceRecordTimer.hpp"

struct PerformanceRecord {
    // How many times a function is invoked.
    uint64_t count = 0;
    // Wall clock time in total of unit nanoseconds or tsc clock cycle.
    uint64_t wall_clock_counter = 0;
    //Name of record
    const char *name = NULL;
    //Full path of file
    const char *file = NULL;
    //Line number in file
    int line_number;
};

class PerformanceRecorder {
public:
    // Accumulate time.
    void record(size_t hash, const char *file, int line_number, const char *name, const PerformanceRecordTimer &timer, const int count = 1) {
        PerformanceRecord &performanceRecord = records[hash];
        performanceRecord.wall_clock_counter += timer.get_wall_clock_elapsed_count();
        performanceRecord.count += count;
        if(performanceRecord.name == NULL) {
            performanceRecord.name = name;
            performanceRecord.file = file;
            performanceRecord.line_number = line_number;
        }
    }

    void clear();

    // Print formatted statistics into output_stream.
    void print(std::ostream &output_stream);
private:
    using records_map = std::map<size_t, PerformanceRecord>;
    records_map records;
    uint64_t counter_per_ms = 0;
};

extern PerformanceRecorder g_performance_recorder;

#endif //C__TEST_PERFORMANCERECORDER_HPP
