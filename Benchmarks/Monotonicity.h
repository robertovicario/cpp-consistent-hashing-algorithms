/**
 * @authors Amos Brocco, Roberto Vicario
 */

#pragma once

#include <boost/unordered/unordered_flat_map.hpp>
#include <cstdint>
#include <iostream>
#include <string>

using namespace std;

template <typename Engine>
double computeMonotonicity(const string& algorithm, uint32_t initNodes) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes);

    /*
     * Starting the measuring.
     */
    uint32_t* bucket_status = new uint32_t[initNodes]();
    for (uint32_t i = 0; i < initNodes; i++) {
        bucket_status[i] = 1;
    }

    uint32_t numRemovals = initNodes / 5;
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
    for (uint32_t i = 0; i < initNodes; i++) {
        auto a = rand();
        auto b = rand();

        if (bucket.contains({a, b})) {
            continue;
        }

        auto target = engine.getBucketCRC32c(a, b);
        bucket.insert({{a, b}, target});

        if (!bucket_status[target]) {
            cout << "# [ERR] ----- Unable to process the node: " << i << "." << endl;
        }
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
    for (uint32_t i = 0; i < initNodes; i++) {
        auto a = rand();
        auto b = rand();

        if (bucket.contains({a, b})) {
            continue;
        }

        auto target = engine.getBucketCRC32c(a, b);
        bucket.insert({{a, b}, target});

        if (!bucket_status[target]) {
            cout << "# [ERR] ----- Unable to process the node: " << i << "." << endl;
        }
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
    double monotonicity = (static_cast<double>(combined_misplaced) / (2 * initNodes)) * 100.0;
    cout << "# [LOG] ----- @" << algorithm << "\t>_ monotonicity = " << monotonicity << " %" << endl;
    return monotonicity;
}
