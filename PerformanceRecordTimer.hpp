//
// Created by 胡磊 on 2021/5/7.
//

#ifndef C__TEST_PERFORMANCERECORDTIMER_HPP
#define C__TEST_PERFORMANCERECORDTIMER_HPP

#ifdef PERFORMANCE_PROFILE

#include <cstdint>

#ifdef CONST_TSC_SUPPORT
#include <chrono>
#include <thread>
#elif defined(_WIN32)

#else
#include <chrono>
#endif

class PerformanceRecordTimer {

#ifdef CONST_TSC_SUPPORT
    typedef uint64_t clock_unit;
#elif defined _WIN32
    typedef struct {
        FILETIME ft_[4];
    } clock_unit;
#else
    typedef std::chrono::time_point<std::chrono::steady_clock> clock_unit;
#endif

public:
    PerformanceRecordTimer(size_t hash, const char *file, const int line, const char *name)
        :hash(hash),
        file(file),
        line(line),
        name(name),
        invocation(0){
        wall_clock_start = get_count();
    }

    ~PerformanceRecordTimer();

    uint64_t get_wall_clock_elapsed_count() const {
#ifdef CONST_TSC_SUPPORT
        return get_count() - wall_clock_start;
#elif defined _WIN32
        clock_unit now = get_count();
        ULARGE_INTEGER u[4];
        u[0].LowPart = wall_clock_start.ft_[2].dwLowDateTime;
        u[0].HighPart = wall_clock_start.ft_[2].dwHighDateTime;
        u[1].LowPart = wall_clock_start.ft_[3].dwLowDateTime;
        u[1].HighPart = wall_clock_start.ft_[3].dwHighDateTime;
        u[2].LowPart = now.ft_[2].dwLowDateTime;
        u[2].HighPart = now.ft_[2].dwHighDateTime;
        u[3].LowPart = now.ft_[3].dwLowDateTime;
        u[3].HighPart = now.ft_[3].dwHighDateTime;
        uint64_t user = (u[2].QuadPart - u[0].QuadPart) * 100;
        uint64_t kernel = (u[3].QuadPart - u[1].QuadPart) * 100;
        return user + kernel;
#else
        auto end = get_count();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
                end - wall_clock_start)
                .count();
#endif
    }

    static uint64_t get_counter_per_ms(){
        if(counter_per_ms == 0) {
#ifdef CONST_TSC_SUPPORT
            counter_per_ms = test_tsc_frequency();
#elif defined _WIN32
            counter_per_ms = 10000;
#else
            counter_per_ms = 1000000;
#endif
        }
        return counter_per_ms;
    }

    void count(){
        invocation++;
    }

private:
    clock_unit get_count() const{
#ifdef CONST_TSC_SUPPORT
        return rdtsc();
#elif defined _WIN32
        clock_unit cur_time;
        ::GetProcessTimes(::GetCurrentProcess(), &cur_time.ft_[0], &cur_time.ft_[1], &cur_time.ft_[2], &cur_time.ft_[3]);
        return cur_time;
#else
        return std::chrono::steady_clock::now();
#endif
    }

#ifdef CONST_TSC_SUPPORT
    static uint64_t rdtsc()
    {
        unsigned int lo, hi;
        __asm__ __volatile__("rdtsc" : "=a" (lo), "=d" (hi));
        return (uint64_t) hi << 32 | lo;
    }

    static uint64_t test_tsc_frequency(){
        auto start = std::chrono::steady_clock::now();
        uint64_t start_count = rdtsc();
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
        uint64_t end_count = rdtsc();
        auto end = std::chrono::steady_clock::now();
        auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                end - start)
                .count();
        return (end_count - start_count) / elapsed_ms;
    }
#endif

private:
    const char *file;
    const int line;
    const char *name;
    const size_t hash;
    int invocation;
    clock_unit wall_clock_start;
    static uint64_t counter_per_ms;
};

#endif // PERFORMANCE_PROFILE

#endif //C__TEST_PERFORMANCERECORDTIMER_HPP
