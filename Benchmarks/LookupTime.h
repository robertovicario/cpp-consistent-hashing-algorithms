/**
 * @authors Amos Brocco, Roberto Vicario
 */

#pragma once

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

template <typename Engine>
double computeLookupTime(const string& algorithm, uint32_t initNodes, uint32_t initNodes2) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, initNodes2);

    /*
     * Measuring.
     */
    vector<double> results;
    volatile int64_t bucket{0};

    for (uint32_t i = 0; i < initNodes; i++) {
        auto start{clock()};
        bucket = engine.getBucketCRC32c(rand(), rand());
        auto end{clock()};

        auto time{static_cast<double>(end - start) / CLOCKS_PER_SEC * pow(10, 9)};
        results.push_back(time);
    }

    double sum_time = 0;
    for (const auto& time : results) {
        sum_time += time;
    }

    /*
     * Returning the results.
     */
    double mean_time = sum_time / results.size();
    cout << "# [LOG] ----- @" << algorithm << "\t>_ lookup_time = " << mean_time << " ns" << endl;
    return mean_time;
}
