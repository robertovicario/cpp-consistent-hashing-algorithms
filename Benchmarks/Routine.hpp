/**
 * @file Routine.hpp
 * @brief Header file containing functions to execute benchmarks.
 * @author Roberto Vicario
 */

#pragma once

#include <cmath>
#include <iostream>
#include <yaml-cpp/yaml.h>

#include "Balance.h"
#include "InitTime.h"
#include "Metrics.h"
#include "../Handler/HandlerImpl.hpp"

using namespace std;

void printInfo(int k, const string& algorithm, const string& benchmark, const string& hashFunction, int initNodes, int iterationsRun) {
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

template <typename Engine>
static void execute(const string& algorithm, HandlerImpl& handler, YAML::Node yaml) {
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
    bool flag = false; // Used to ignore benchmarks not implemented yet.
    for (auto i : yaml["benchmarks"]) {
        auto benchmark = i["name"].as<string>();
        /*
         * HASH_FUNCTIONS
         *
         * ![WARNING]
         * For this version of the software, we have used only "crc32".
         */
        // for (auto j: yaml["common"]["hash-functions"]) {
            // auto hashFunction = j.as<string>();
            string hashFunction = "crc32"; // remove this line to use the previous code
            /*
             * INIT_NODES
             */
            for (auto j: yaml["common"]["init-nodes"]) {
                auto initNodes = j.as<int>();
                /*
                 * ITERATIONS_RUN
                 */
                for (int k = 0; k < iterationsRun; k++) {
                    /*
                     * BENCHMARKS
                     */
                    if (benchmark == "balance") {
                        printInfo(k, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[k] = computeBalance<Engine>(algorithm, initNodes);
                    } else if (benchmark == "init-time") {
                        printInfo(k, algorithm, benchmark, hashFunction, initNodes, iterationsRun);
                        results[k] = computeInitTime<Engine>(algorithm, initNodes);
                    } else {
                        flag = true;
                        break;
                    }
                }

                if (!flag) {
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
                } else {
                    cout << "# [ERR] ----- Benchmark not implemented yet." << endl;
                    cout << "#" << endl;
                    break;
                }
            }
        // }
    }
}
