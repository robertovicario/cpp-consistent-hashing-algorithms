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

template <typename Engine>
double computeResizeTime(const string& algorithm, uint32_t initNodes) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes);

    /*
     * Selecting a random bucket index.
     */
    random_device rd;
    mt19937 rng(rd());
    uint32_t index = rng() % initNodes;

    /*
     * Starting the measuring.
     */
    auto start{clock()};

    vector<uint32_t> bucket_status(initNodes, 1);
    auto removed_node = engine.removeBucket(index);
    bucket_status[removed_node] = 0;

    auto end{clock()};

    /*
     * Returning the results.
     */
    auto time{static_cast<double>(end - start) / CLOCKS_PER_SEC * pow(10, 9)};
    cout << "# [LOG] ----- @" << algorithm << "\t>_ resize_time = " << time << " ns" << endl;
    return time;
}
