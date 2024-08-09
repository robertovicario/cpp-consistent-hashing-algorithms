/**
 * @authors Amos Brocco, Roberto Vicario
 */

#pragma once

#include <chrono>
#include <cmath>
#include <iostream>
#include <random>
#include <vector>
#include <yaml-cpp/yaml.h>

#include "../Handler/HandlerImpl.hpp"

using namespace std;
using namespace std::chrono;

template <typename Engine, typename... Args>
double computeLookupTime(const YAML::Node& yaml, const string& algorithm, uint32_t initNodes, Args... args) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

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
    double sumTime = 0;
    for (uint32_t i = 0; i < initNodes; i++) {
        auto start{high_resolution_clock::now()};

        engine.getBucketCRC32c(rand(), rand());

        auto end{high_resolution_clock::now()};
        auto duration = duration_cast<nanoseconds>(end - start).count();

        sumTime += duration;
    }

    double meanTime = sumTime / initNodes;

    /*
     * Handling the time unit.
     */
    if (unit == "SECONDS") {
        meanTime /= 1e9;
    } else if (unit == "MILLISECONDS") {
        meanTime /= 1e6;
    } else if (unit == "MICROSECONDS") {
        meanTime /= 1e3;
    }

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ lookup_time = " << meanTime << " " << unit << endl;
    return meanTime;
}
