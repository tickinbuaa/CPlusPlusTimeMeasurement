//
// Created by 胡磊 on 2021/5/7.
//

#include <chrono>
#include "PerformanceRecordTimer.hpp"
#include "PerformanceRecorder.hpp"

uint64_t PerformanceRecordTimer::counter_per_ms = 0;

PerformanceRecordTimer::~PerformanceRecordTimer() {
    g_performance_recorder.record(hash, file, line, name, *this, invocation);
}