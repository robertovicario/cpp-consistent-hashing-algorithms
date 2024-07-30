/**
 * @author Roberto Vicario
 */

#pragma once

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;

template <typename Engine, typename... Args>
double computeResizeTime(const YAML::Node& yaml, const string& algorithm, u_int32_t initNodes, Args... args) {
    auto start{clock()};

    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

    /*
     * Selecting a random bucket index.
     */
    random_device rd;
    mt19937 rng(rd());
    uint32_t index = rng() % initNodes;

    /*
     * Measuring.
     */
    vector<uint32_t> bucket_status(initNodes, 1);
    auto removed_node = engine.removeBucket(index);
    bucket_status[removed_node] = 0;

    auto end{clock()};

    /*
     * Returning the results.
     */
    double time{static_cast<double>(end - start) / CLOCKS_PER_SEC * pow(10, 9)};
    cout << "# [LOG] ----- @" << algorithm << "\t>_ resize_time = " << time << " ns" << endl;
    return time;
}
