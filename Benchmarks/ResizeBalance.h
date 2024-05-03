/**
 * @authors Amos Brocco, Roberto Vicario
 */

#include <iostream>
#include <random>

using namespace std;

template <typename Engine>
double computeResizeBalance(const string& algorithm, uint32_t initNodes) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes);

    /*
     * Selecting the random bucket index.
     */
    random_device rd;
    mt19937 rng(rd());

    vector<uint32_t> bucket_status(initNodes, 1);
    uint32_t i = 0;

    uint32_t numRemovals = initNodes / 5;
    while (i < numRemovals) {
        uint32_t index = rng() % initNodes;
        if (bucket_status[index] == 1) {
            auto removed_node = engine.removeBucket(index);
            bucket_status[removed_node] = 0;
            i++;
        }
    }

    /*
     * Absorbing keys into the anchor set.
     */
    vector<uint32_t> absorbed_keys(initNodes, 0);
    for (i = 0; i < initNodes; i++) {
        absorbed_keys[engine.getBucketCRC32c(rng(), rng())] += 1;
    }

    /*
     * Starting the measuring.
     */
    double mean = static_cast<double>(initNodes) / (initNodes - numRemovals);
    double balance = 0;

    for (i = 0; i < initNodes; i++) {
        if (bucket_status[i]) {
            if (balance < (absorbed_keys[i] / mean)) {
                balance = absorbed_keys[i] / mean;
            }
        } else if (0 < absorbed_keys[i]) {
            cout << "# [ERR] ----- Unable to process the node: " << i << "." << endl;
        }
    }

    /**
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ balance = " << balance << endl;
    return balance;
}
