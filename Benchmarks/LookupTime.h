/**
 * @authors Amos Brocco, Roberto Vicario
 */

#pragma once

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;

template <typename Engine>
double computeLookupTime(const string& algorithm, uint32_t initNodes) {
    /*
     * Starting the measuring.
     */
    auto start{clock()};

    /*
     * Initializing the engine.
     */
    Engine engine(initNodes);

    /*
     * Selecting a random bucket index.
     */
    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<uint32_t> dist(0, initNodes - 1);
    uint32_t index = dist(rng);

    /*
     * Measuring.
     */
    volatile int64_t bucket{0};
    for (uint32_t i = 0; i < initNodes; i++) {
         bucket = engine.getBucketCRC32c(rand(), rand());
    }

    auto end{clock()};

    /*
     * Returning the results.
     */
    auto time{static_cast<double>(end - start) / CLOCKS_PER_SEC * pow(10, 9)};
    cout << "# [LOG] ----- @" << algorithm << "\t>_ lookup_time = " << time << " ns" << endl;
    return time;
}
