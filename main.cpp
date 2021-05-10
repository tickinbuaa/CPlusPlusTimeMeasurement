#include <iostream>

#include <time.h>
#include <stdio.h>
#include <map>
#include <vector>
#include <unistd.h>
#include <thread>
#include <iostream>
using namespace std;
#include "profile.hpp"
#include "Timer.hpp"

int main() {
    constexpr int LOOP_COUNT = 100000000;
    Timer timer1;
    for (int j = 0; j < LOOP_COUNT;j++){
        performance_test("mytefdsastfdfdsafdsafd",);
    }
    timer1.PrintElapsed("Total:");

    Timer timer2;
    for (int j = 0; j < LOOP_COUNT;j++){
        performance_test("mytefdsast",);
    }
    timer2.PrintElapsed("Total:");

    Timer timer3;
    uint64_t accumulated = 0;
    for (int j = 0; j < LOOP_COUNT;j++){
        auto before = std::chrono::steady_clock::now();
        accumulated += std::chrono::duration_cast<std::chrono::nanoseconds>(
           std::chrono::steady_clock::now() - before).count();
    }
    timer3.PrintElapsed("Total:");
    cout << accumulated << endl;

    performance_test("mytfdsafdsafdafest",);
    performance_test("mygfdshrtgrcsgdfsgtest",);
    performance_test("mytfdvc vs trs bdsbsest",);
    performance_test("mytestfdsgre bns bds g a ga",);
    performance_test("mytgfd sbvctesb x nfdest",);
    performance_test("myt vdsgrag rsb est",);
    performance_test("mytv cdsgagr bcx csgra est",);
    performance_test("mytv cdsgagr bcx csgfdsafdsafra est",);
    performance_test("mytv cdsgagr bcx csgb vcscgdfs ra est",);
    performance_test("mytv cdsgagr bcx cvdscgxsb dfs vfaea vc sgra est",);
    Timer timer;
    for (int j = 0; j < LOOP_COUNT;j++){
        performance_test("mytest",);
    }
    timer.PrintElapsed("Total:");

    Timer nest_loop_timer;
    int sum = 0;
    performance_test_loop("loop-test-outer", for(int i = 0, k = 0; i < LOOP_COUNT; i++, k++), performance_test_loop("loop-test-inner", for (int j = 0; j < 100; j++), sum++;))
    nest_loop_timer.PrintElapsed("Total[nested-for]:");

    Timer loop_timer;
    performance_test_loop("loop-test-outer", for(int i = 0, k = 0; i < LOOP_COUNT; i++, k++), sum++)
    loop_timer.PrintElapsed("Total[for]:");

    sum = LOOP_COUNT;
    Timer while_loop_timer;
    performance_test_loop("while-test", while(sum >= 0), sum--;)
    while_loop_timer.PrintElapsed("Total[while]:");
    print_performance_statistics(cout);

    const char *file = __FILE__;


    int line = __LINE__;
    cout << file << line << endl;
}


