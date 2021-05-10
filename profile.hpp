//
// Created by 胡磊 on 2021/5/3.
//

#ifndef CHIAPOS_PROFILE_HPP
#define CHIAPOS_PROFILE_HPP

#define PERFORMANCE_PROFILE

#ifdef PERFORMANCE_PROFILE
#include <chrono>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

#include "PerformanceRecorder.hpp"
#include "PerformanceRecordTimer.hpp"

/*
 *  Performance record for specific function or code segment.
 */

constexpr int constexpr_strlen(const char *name) {
    int i = 0;
    while (name[i] != '\0') i++;
    return i;
}

constexpr size_t hash_str( const char *file, int line, const char *name) {
    size_t hash = line;
    int length = constexpr_strlen(name);
    for (int i = 0; i < length; i++) {
        hash *= 23;
        hash += name[i];
    }

    length = constexpr_strlen(file);
    for (int i = 0; i < length; i++) {
        hash *= 23;
        hash += file[i];
    }
    return hash;
}

#define performance_test(name, call)                                                                        \
    {                                                                                                       \
        constexpr size_t hash = hash_str(__FILE__, __LINE__, name);                                         \
        auto __performance_test_timer__ = PerformanceRecordTimer(hash, __FILE__, __LINE__, name);           \
        __performance_test_timer__.count();                                                                 \
        call;                                                                                               \
    }

#define performance_record(name, timer, count)                                                              \
    {                                                                                                       \
        constexpr size_t hash = hash_str(__FILE__, __LINE__, name);                                         \
        g_performance_recorder.record(hash, __FILE__, __LINE__, name, timer, count);                        \
    }

#define print_performance_statistics(ostream) g_performance_recorder.print(ostream)

#define performance_test_loop(name, header, body)                                                           \
{                                                                                                           \
    constexpr size_t hash = hash_str(__FILE__, __LINE__, name);                                             \
    auto __performance_test_timer__ = PerformanceRecordTimer(hash, __FILE__, __LINE__, name);               \
    header                                                                                                  \
    {                                                                                                       \
        __performance_test_timer__.count();                                                                 \
        body;                                                                                               \
    }                                                                                                       \
}

#else

#define performance_test(name, call) call
#define performance_record(name, timer, count)
#define print_performance_statistics(ostream)
#define performance_test_loop(name, header, body) \
    header{                                       \
        body;                                     \
    }
#endif  // PERFORMANCE_PROFILE
#endif  // CHIAPOS_PROFILE_HPP
