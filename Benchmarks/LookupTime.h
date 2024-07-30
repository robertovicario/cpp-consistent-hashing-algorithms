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
double computeLookupTime(const YAML::Node& yaml, const string& algorithm, u_int32_t initNodes, Args... args) {
    /*
     * Initializing the engine with the provided arguments.
     */
    Engine engine(initNodes, args...);

    /*
     * Starting the measuring.
     */
    vector<double> results;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, INT32_MAX);

    for (uint32_t i = 0; i < initNodes; i++) {
        auto start{clock()};
        engine.getBucketCRC32c(dist(gen), dist(gen));
        auto end{clock()};

        auto time{static_cast<double>(end - start) / CLOCKS_PER_SEC * pow(10, 9)};
        results.push_back(time);
    }

    double sum_time = 0;
    for (const auto& time : results) {
        sum_time += time;
    }

    /*
     * Returning the results.
     */
    double mean_time = sum_time / results.size();
    cout << "# [LOG] ----- @" << algorithm << "\t>_ lookup_time = " << mean_time << " ns" << endl;
    return mean_time;
}
