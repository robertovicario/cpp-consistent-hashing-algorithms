/**
 * @author Roberto Vicario
 */

#pragma once

#include <chrono>
#include <cmath>
#include <iostream>

using namespace std;
using namespace std::chrono;

template <typename Engine>
double computeInitTime(const string& algorithm, uint32_t initNodes) {
    /*
     * Starting the measuring.
     */
    auto start{clock()};
    Engine engine(initNodes);
    auto end{clock()};

    /*
     * Returning the results.
     */
    auto time{static_cast<double>(end - start) / CLOCKS_PER_SEC * pow(10, 9)};
    cout << "# [LOG] ----- @" << algorithm << "\t>_ init_time = " << time << " ns" << endl;
    return time;
}
