/**
 * @author Roberto Vicario
 */

#pragma once

#include <iostream>
#include <cmath>
#include <yaml-cpp/yaml.h>

#include "InitTime.h"
#include "../Handler/HandlerImpl.h"

using namespace std;

double computeMean(const double results[], int size) {
    double sum = 0;
    for (int i = 0; i < size; i++) {
        sum += results[i];
    }

    return sum / size;
}

double computeVariance(const double results[], int size) {
    double mean = computeMean(results, size);
    double sumSquaredDiff = 0;

    for (int i = 0; i < size; i++) {
        sumSquaredDiff += pow(results[i] - mean, 2);
    }

    return sumSquaredDiff / size;
}

template <typename Engine>
static void execute(HandlerImpl& handler, YAML::Node yaml) {
    /**
     * Executing the benchmark routine.
     */
    auto iterationsRun = yaml["common"]["iterations"]["run"].as<int>();
    double results[iterationsRun];
    double mean;
    double variance;

    /**
     * BENCHMARKS
     */
    // for (auto i : yaml["benchmarks"]) {
        // auto benchmark = i["name"].as<string>();
        /**
         * ![WARNING]
         * For this version of the software, we used only "crc32".
         */
        for (auto j: yaml["common"]["hash-functions"]) {
            auto hashFunction = j.as<string>();
            if (hashFunction == "crc32") {
                /**
                 * INIT_NODES
                 */
                for (auto k: yaml["common"]["init-nodes"]) {
                    auto initNodes = k.as<int>();

                    cout << "# [LOG] ----- Benchmark  : (name = " << "balance" << ")" << endl;
                    cout << "# [LOG] ----- Parameters : (algorithm = " << "dx" << ", hash_function = " << hashFunction << ", init_nodes = " << initNodes << ")" << endl;
                    cout << "# [LOG] ----- Iterations : (warmup = " << 0 << ", run = " << iterationsRun << ")" << endl;
                    cout << "#" << endl;

                    /**
                     * ITERATIONS_RUN
                     */
                    for (int l = 0; l < iterationsRun; l++) {
                        results[l] = computeInitTime<Engine>("dx", initNodes, initNodes);
                    }

                    cout << "#" << endl;

                    /**
                     * Updating new data to the CSV file.
                     */
                    mean = computeMean(results, iterationsRun);
                    variance = computeVariance(results, iterationsRun);
                    handler.updateData("dx", "balance", hashFunction, initNodes, iterationsRun, mean, variance);
                }
            }
        }
    // }
}
