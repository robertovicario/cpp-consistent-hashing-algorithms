/**
 * @author Roberto Vicario
 */

#pragma once

#include <chrono>
#include <cmath>
#include <iostream>

using namespace std;
using namespace std::chrono;

template <typename Engine, typename... Args>
double computeInitTime(const YAML::Node& yaml, const string& algorithm, u_int32_t initNodes, Args... args) {
    /*
     * Starting the measuring.
     */
    auto start{clock()};
    Engine engine(initNodes, args...);
    auto end{clock()};

    /*
     * Returning the results.
     */
    double time{static_cast<double>(end - start) / CLOCKS_PER_SEC * pow(10, 9)};
    cout << "# [LOG] ----- @" << algorithm << "\t>_ init_time = " << time << " ns" << endl;
    return time;
}
