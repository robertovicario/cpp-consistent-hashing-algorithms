/**
 * @authors Amos Brocco, Roberto Vicario
 */

#pragma once

#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

template <typename Engine>
double computeResizeBalance(const string& algorithm, const uint32_t& initNodes) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes);

    /*
     * Selecting the random bucket index.
     */
    random_device rd;
    mt19937 rng(rd());

    vector<uint32_t> bucketStatus(initNodes, 1);
    uint32_t removalCount = 0;
    uint32_t numRemovals = initNodes / 5;

    while (removalCount < numRemovals) {
        uint32_t index = rng() % initNodes;
        if (bucketStatus[index] == 1) {
            auto removedNode = engine.removeBucket(index);
            bucketStatus[removedNode] = 0;
            removalCount++;
        }
    }

    /*
     * Absorbing keys into the anchor set.
     */
    vector<uint32_t> absorbedKeys(initNodes, 0);
    for (uint32_t i = 0; i < initNodes; i++) {
        absorbedKeys[engine.getBucketCRC32c(rng(), rng())]++;
    }

    /*
     * Starting the measuring.
     */
    double mean = initNodes > numRemovals ? static_cast<double>(initNodes) / (initNodes - numRemovals) : 0;
    double balance = 0;

    for (uint32_t i = 0; i < initNodes; i++) {
        if (bucketStatus[i]) {
            if (balance < (absorbedKeys[i] / mean)) {
                balance = absorbedKeys[i] / mean;
            }
        } else if (absorbedKeys[i] > 0) {
            cerr << "# [ERR] ----- Unable to process the node: " << i << "." << endl;
        }
    }

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ resize_balance = " << balance << endl;
    return balance;
}
