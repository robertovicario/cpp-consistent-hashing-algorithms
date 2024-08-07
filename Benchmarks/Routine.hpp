/**
 * @author Roberto Vicario
 */

#pragma once

#include <cmath>
#include <iostream>
#include <yaml-cpp/yaml.h>

#include "Balance.h"
#include "InitTime.h"
#include "LookupTime.h"
#include "MemoryUsage.h"
#include "Metrics.h"
#include "Monotonicity.h"
#include "ResizeBalance.h"
#include "ResizeTime.h"
#include "../Handler/HandlerImpl.hpp"

using namespace std;

void printInfo(int k, const string& algorithm, const string& benchmark, const string& hashFunction, u_int32_t initNodes, u_int32_t iterationsRun) {
    /*
     * Printing the information.
     */
    if (k == 0) {
        cout << "# [LOG] ----- Benchmark  : (name = " << benchmark << ")" << endl;
        cout << "# [LOG] ----- Parameters : (algorithm = " << algorithm << ", hash_function = " << hashFunction << ", init_nodes = " << initNodes << ")" << endl;
        cout << "# [LOG] ----- Iterations : (run = " << iterationsRun << ")" << endl;
        cout << "#" << endl;
        cout << "# [SYS] ----- Computing ..." << endl;
        cout << "#" << endl;
    }
}

template <typename Engine, typename... Args>
static void execute(HandlerImpl& handler, YAML::Node yaml, const string& algorithm, Args... args) {
    /*
     * Initializing the metrics.
     */
    auto iterationsRun = yaml["common"]["iterations"]["run"].as<int>();
    double results[iterationsRun];
    double mean;
    double var;
    double stddev;

    /*
     * Executing the benchmark routine.
     */
    for (auto i : yaml["benchmarks"]) {
        auto benchmark = i["name"].as<string>();
        /*
         * HASH_FUNCTIONS
         *
         * [!WARNING]
         * For this version of the software, we have used only "crc32".
         */
        // for (auto j: yaml["common"]["hash-functions"]) {
            // auto hashFunction = j.as<string>();
            string hashFunction = "crc32"; // remove this line to use the previous code
            /*
             * INIT_NODES
             */
            for (auto k: yaml["common"]["init-nodes"]) {
                auto initNodes = k.as<int>();
                /*
                 * ITERATIONS_RUN
                 */
                for (int l = 0; l < iterationsRun; l++) {
                    /*
                     * BENCHMARKS
                     */
                    if (benchmark == "balance") {
                        /*
                         * BALANCE
                         */
                        printInfo(l, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[l] = computeBalance<Engine>(yaml, algorithm, initNodes, args...);
                    } else if (benchmark == "init-time") {
                        /*
                         * INIT_TIME
                         */
                        printInfo(l, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[l] = computeInitTime<Engine>(yaml, algorithm, initNodes, args...);
                    } else if (benchmark == "lookup-time") {
                        /*
                         * LOOKUP_TIME
                         */
                        printInfo(l, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[l] = computeLookupTime<Engine>(yaml, algorithm, initNodes, args...);
                    } else if (benchmark == "memory-usage") {
                        /*
                         * MEMORY_USAGE
                         */
                        printInfo(l, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[l] = computeMemoryUsage<Engine>(yaml, algorithm, initNodes, args...);
                    } else if (benchmark == "monotonicity") {
                        /*
                         * MONOTONICITY
                         */
                        printInfo(l, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[l] = computeMonotonicity<Engine>(yaml, algorithm, initNodes, args...);
                    } else if (benchmark == "resize-balance") {
                        /*
                         * RESIZE_BALANCE
                         */
                        printInfo(l, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[l] = computeResizeBalance<Engine>(yaml, algorithm, initNodes, args...);
                    } else if (benchmark == "resize-time") {
                        /*
                         * RESIZE_TIME
                         */
                        printInfo(l, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[l] = computeResizeTime<Engine>(yaml, algorithm, initNodes, args...);
                    }
                }

                /*
                 * Returning the results.
                 */
                cout << "#" << endl;
                cout << "# [SYS] ----- Computing ... " << endl;

                mean = computeMean(results, iterationsRun);
                var = computeVar(results, iterationsRun);
                stddev = computeStdDev(results, iterationsRun);

                cout << "#" << endl;
                cout << "# [LOG] ----- Results : (mean = " << mean << ", var = " << var << ", stddev = " << stddev << ")" << endl;
                cout << "#" << endl;

                /*
                 * Updating the new data to the CSV file.
                 */
                handler.updateData(algorithm, benchmark, hashFunction, initNodes, iterationsRun, mean, var, stddev);
                cout << "#" << endl;
            }
        // }
    }
}
