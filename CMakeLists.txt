cmake_minimum_required(VERSION 3.19)
project(C__Test)

set(CMAKE_CXX_STANDARD 14)

add_executable(C__Test main.cpp PerformanceRecorder.cpp PerformanceRecorder.hpp PerformanceRecordTimer.cpp PerformanceRecordTimer.hpp Timer.cpp Timer.hpp)
message(STATUS "${CMAKE_CXX_FLAGS}")
message(STATUS "${CMAKE_C_FLAGS}")
