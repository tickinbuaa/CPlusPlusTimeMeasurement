//
// Created by 胡磊 on 2021/5/7.
//

#ifndef C__TEST_TIMER_HPP
#define C__TEST_TIMER_HPP
#include <cassert>
#include <chrono>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>
#include <unistd.h>


class Timer {
public:
    Timer()
    {
        wall_clock_time_start_ = std::chrono::steady_clock::now();
#if _WIN32
        ::GetProcessTimes(::GetCurrentProcess(), &ft_[3], &ft_[2], &ft_[1], &ft_[0]);
#else
        cpu_time_start_ = clock();
#endif
    }

    static char *GetNow()
    {
        auto now = std::chrono::system_clock::now();
        auto tt = std::chrono::system_clock::to_time_t(now);
        return ctime(&tt);  // ctime includes newline
    }

    void PrintElapsed(const std::string &name) const
    {
        auto wall_clock_ms = get_wall_clock_ns() / 1000.0 / 1000;

        double cpu_time_ms = get_cpu_ticks() * 1000.0 / CLOCKS_PER_SEC ;

        double cpu_ratio = static_cast<int>(10000 * (cpu_time_ms / wall_clock_ms)) / 100.0;

        std::cout << name << " " << (wall_clock_ms / 1000.0) << " seconds. CPU (" << cpu_ratio
                  << "%) " << Timer::GetNow();
    }

    uint64_t get_wall_clock_ns() const{
#if _WIN32
        FILETIME nowft_[6];
        nowft_[0] = ft_[0];
        nowft_[1] = ft_[1];

        ::GetProcessTimes(::GetCurrentProcess(), &nowft_[5], &nowft_[4], &nowft_[3], &nowft_[2]);
        ULARGE_INTEGER u[4];
        for (size_t i = 0; i < 4; ++i) {
            u[i].LowPart = nowft_[i].dwLowDateTime;
            u[i].HighPart = nowft_[i].dwHighDateTime;
        }
        uint64_t user = (u[2].QuadPart - u[0].QuadPart) * 100;
        uint64_t kernel = (u[3].QuadPart - u[1].QuadPart) * 100;
        return user + kernel;
#else
        auto end = std::chrono::steady_clock::now();
        return std::chrono::duration_cast<std::chrono::nanoseconds>(
                end - this->wall_clock_time_start_)
                .count();
#endif
    }

    clock_t get_cpu_ticks() const{
        return clock() - this->cpu_time_start_;
    }

private:
    std::chrono::time_point<std::chrono::steady_clock> wall_clock_time_start_;
#if _WIN32
    FILETIME ft_[4];
#else
    clock_t cpu_time_start_;
#endif

};


#endif //C__TEST_TIMER_HPP
