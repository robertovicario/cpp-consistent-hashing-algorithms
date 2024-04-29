/**
 * @author Roberto Vicario
 */

#pragma once

#include <iostream>
#include <yaml-cpp/yaml.h>

#include "Balance.h"
#include "InitTime.h"
#include "MemoryUsage.h"
#include "Monotonicity.h"
#include "LookupTime.h"
#include "ResizeBalance.h"
#include "ResizeTime.h"

using namespace std;

template<typename Engine>
static void execute(YAML::Node config, string algorithm,
                uint32_t anchor_set, uint32_t working_set,
                uint32_t num_removals, uint32_t num_keys) {
    /**
     * Starting benchmark routine.
     */
    cout << "#" << endl;
    cout << "# [LOG] ----- Parameters: (algorithm = " << algorithm << ", function = crc32, initNodes = " << working_set << ")" << endl;
    cout << "#" << endl;
    cout << "#" << endl;
    
    for (const auto &iter: config["benchmarks"]) {
        auto benchmark = iter["name"].as<string>();
        if (benchmark == "balance") {
            computeBalance<Engine>(algorithm, anchor_set, working_set, num_removals, num_keys);
        } else if (benchmark == "init-time") {
            computeInitTime<Engine>(algorithm, anchor_set, working_set);
        } else if (benchmark == "lookup-time") {
            computeLookupTime<Engine>(algorithm, "speed_test.log", anchor_set, working_set, num_removals, num_keys);
        } else if (benchmark == "memory-usage") {
            computeMemoryUsage<Engine>(algorithm, anchor_set, working_set);
        } else if (benchmark == "monotonicity") {
            computeMonotonicity<Engine>(algorithm, "monotonicity.log", anchor_set, working_set, num_removals, num_keys);
        } else if (benchmark == "resize-balance") {
            computeResizeBalance<Engine>(algorithm, anchor_set, working_set);
        } else if (benchmark == "resize-time") {
            computeResizeTime<Engine>(algorithm, anchor_set, working_set);
        }
    }

    /**
     * Closing single benchmark routine.
     */
    cout << "#" << endl;
    cout << "#" << endl;
}
