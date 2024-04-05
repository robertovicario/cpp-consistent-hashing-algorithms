/**
 * @author Roberto Vicario
 */

#pragma once

#include <chrono>
#include <iostream>

using namespace std;
using namespace std::chrono;

template <typename Algorithm>
int computeResizeTime(string algorithm, uint32_t anchor_set, uint32_t working_set) {
    Algorithm engine(anchor_set, working_set);

    auto start{clock()};

    // CODE

    auto end{clock()};

    auto time{static_cast<double>(end - start) / CLOCKS_PER_SEC};
    cout << "# [LOG] ----- @" << algorithm << "\t>_ resize_time    = " << time << " seconds" << endl;

    return 0;
}
