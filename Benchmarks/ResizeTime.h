/**
 * @author Roberto Vicario
 */

#pragma once

#include <chrono>
#include <iostream>
#include <random>

using namespace std;
using namespace std::chrono;

template <typename Algorithm>
int computeResizeTime(string algorithm, uint32_t anchor_set,
                uint32_t working_set) {
    Algorithm engine(anchor_set, working_set);

    /**
     * Selecting random bucket index.
     */
    random_device rd;
    mt19937 rng(rd());
    uint32_t index = rng() % working_set;

    /**
     * Starting measuring.
     */
    auto start{clock()};

    vector<uint32_t> bucket_status(working_set, 1);
    auto removed_node = engine.removeBucket(index);
    bucket_status[removed_node] = 0;

    auto end{clock()};

    /**
     * Printing results.
     */
    auto time{static_cast<double>(end - start) / CLOCKS_PER_SEC};
    cout << "# [LOG] ----- @" << algorithm << "\t>_ resize_time    = " << time << " seconds" << endl;

    return 0;
}
