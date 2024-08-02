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
     * Checking the configuration.
     */
    string unit = "NANOSECONDS";
    if (yaml["common"] && yaml["common"]["time"] && yaml["common"]["time"]["unit"]) {
        unit = yaml["common"]["time"]["unit"].as<string>("NANOSECONDS");
    }

    /*
     * Starting the measuring.
     */
    auto start{high_resolution_clock::now()};

    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

    auto end{high_resolution_clock::now()};
    auto duration = duration_cast<nanoseconds>(end - start).count();

    /*
     * Handling the time unit.
     */
    if (unit == "SECONDS") {
        duration /= 1e9;
    } else if (unit == "MILLISECONDS") {
        duration /= 1e6;
    } else if (unit == "MICROSECONDS") {
        duration /= 1e3;
    }

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ init_time = " << duration << " " << unit << endl;
    return duration;
}
