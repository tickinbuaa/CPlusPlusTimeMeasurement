cmake_minimum_required(VERSION 3.19)
project(C__Test)

set(CMAKE_CXX_STANDARD 14)

add_executable(C__Test main.cpp PerformanceRecorder.cpp PerformanceRecorder.hpp PerformanceRecordTimer.cpp PerformanceRecordTimer.hpp Timer.cpp Timer.hpp)

if (PROFILE)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPERFORMANCE_PROFILE")
    message(STATUS "Performance profile is enabled")
    if (CONST_TSC_SUPPORT)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCONST_TSC_SUPPORT")
        message(STATUS "Constant tsc support is enabled")
    elseif(WIN32)
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_WIN32")
        message(STATUS "Win32 is enabled")
    endif()
endif()

message(STATUS "${CMAKE_CXX_FLAGS}")
message(STATUS "${CMAKE_C_FLAGS}")
