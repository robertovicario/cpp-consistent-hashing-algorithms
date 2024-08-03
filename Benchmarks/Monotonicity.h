/**
 * @authors Amos Brocco, Roberto Vicario
 */

#pragma once

#include <boost/unordered/unordered_flat_map.hpp>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

template <typename Engine, typename... Args>
double computeMonotonicity(const YAML::Node& yaml, const string& algorithm, u_int32_t initNodes, Args... args) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

    /*
     * Checking the configuration.
     */
    double fraction = 0.1;
    int keyMultiplier = 100;

    if (yaml["benchmarks"] && yaml["benchmarks"]["name"] && yaml["benchmarks"]["name"]["monotonicity"]) {
        if (yaml["benchmarks"]["name"]["monotonicity"]["args"]) {
            auto configs = yaml["benchmarks"]["name"]["monotonicity"]["args"];
            if (configs["fractions"]) {
                fraction = configs["fractions"].as<double>(0.1);
            }

            if (configs["keyMultiplier"]) {
                keyMultiplier = configs["keyMultiplier"].as<int>(100);
            }
        }
    }

    /*
     * Starting the measuring.
     */
    auto* bucket_status = new uint32_t[initNodes]();
    for (uint32_t i = 0; i < initNodes; i++) {
        bucket_status[i] = 1;
    }

    /*
     * Selecting the percentage of nodes to remove.
     */
    auto numRemovals = static_cast<uint32_t>(initNodes * fraction);
    for (int i = 0; i < numRemovals;) {
        uint32_t removed = rand() % initNodes;
        if (bucket_status[removed] == 1) {
            auto rnode = engine.removeBucket(removed);
            bucket_status[rnode] = 0;
            i++;
        }
    }

    /*
     * Simulating the removals.
     */
    boost::unordered_flat_map<pair<uint32_t, uint32_t>, uint32_t> bucket;
    for (uint32_t i = 0; i < initNodes * keyMultiplier; i++) {
        auto a = rand();
        auto b = rand();

        if (bucket.contains({a, b})) {
            continue;
        }

        auto target = engine.getBucketCRC32c(a, b);
        bucket.insert({{a, b}, target});
    }

    uint32_t misplaced_after_removal = 0;
    for (const auto& i : bucket) {
        auto oldbucket = i.second;
        auto a = i.first.first;
        auto b = i.first.second;
        auto newbucket = engine.getBucketCRC32c(a, b);

        if (oldbucket != newbucket) {
            misplaced_after_removal++;
        }
    }

    /*
     * Simulating the additions.
     */
    for (uint32_t i = 0; i < initNodes * keyMultiplier; i++) {
        auto a = rand();
        auto b = rand();

        if (bucket.contains({a, b})) {
            continue;
        }

        auto target = engine.getBucketCRC32c(a, b);
        bucket.insert({{a, b}, target});
    }

    uint32_t misplaced_after_addition = 0;
    for (const auto& i : bucket) {
        auto oldbucket = i.second;
        auto a = i.first.first;
        auto b = i.first.second;
        auto newbucket = engine.getBucketCRC32c(a, b);

        if (oldbucket != newbucket) {
            misplaced_after_addition++;
        }
    }

    /*
     * Returning the results.
     */
    double combined_misplaced = misplaced_after_removal + misplaced_after_addition;
    double monotonicity = (static_cast<double>(combined_misplaced) / (2 * initNodes * keyMultiplier)) * 100.0;
    cout << "# [LOG] ----- @" << algorithm << "\t>_ monotonicity = " << monotonicity << " %" << endl;
    delete[] bucket_status;
    return monotonicity;
}
