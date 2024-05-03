/**
 * @authors Amos Brocco, Roberto Vicario
 */

#include <iostream>
#include <random>

using namespace std;

template <typename Engine>
double computeBalance(const string& algorithm, uint32_t initNodes) {
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

    /*
     * Absorbing keys into the anchor set.
     */
    vector<uint32_t> absorbed_keys(initNodes, 0);
    for (uint32_t i = 0; i < initNodes; i++) {
        absorbed_keys[engine.getBucketCRC32c(rng(), rng())] += 1;
    }

    /*
     * Starting the measuring.
     */
    double mean = static_cast<double>(initNodes) / initNodes;
    double balance = 0;

    for (uint32_t i = 0; i < initNodes; i++) {
        if (balance < (absorbed_keys[i] / mean)) {
            balance = absorbed_keys[i] / mean;
        }
    }

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ balance = " << balance << endl;
    return balance;
}
