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
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

    /*
     * Starting the measuring.
     */
    auto start{high_resolution_clock::now()};

    /*
     * Selecting a random bucket.
     */
    random_device rd;
    mt19937 rng(rd());
    uint32_t index = rng() % initNodes;

    /*
     * Applying the resizing.
     */
    vector<uint32_t> bucket_status(initNodes, 1);
    auto removed_node = engine.removeBucket(index);
    bucket_status[removed_node] = 0;

    auto end{high_resolution_clock::now()};
    auto duration = duration_cast<nanoseconds>(end - start).count();

    /*
     * Handling the time unit.
     */
    string unit = "NANOSECONDS";
    if (yaml["common"] && yaml["common"]["time"] && yaml["common"]["time"]["unit"]) {
        unit = yaml["common"]["time"]["unit"].as<string>("NANOSECONDS");
    }

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
    cout << "# [LOG] ----- @" << algorithm << "\t>_ resize_time = " << duration << " " << unit << endl;
    return duration;
}
