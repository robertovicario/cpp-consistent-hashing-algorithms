/**
 * @authors Amos Brocco, Roberto Vicario
 */

#include <iostream>
#include <random>
#include <string>
#include <vector>

using namespace std;

template <typename Engine>
double computeBalance(const string& algorithm, const uint32_t& initNodes) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes);

    /*
     * Absorbing keys into the anchor set.
     */
    random_device rd;
    mt19937 rng(rd());
    vector<uint32_t> absorbedKeys(initNodes, 0);

    for (uint32_t i = 0; i < initNodes; i++) {
        absorbedKeys[engine.getBucketCRC32c(rng(), rng())]++;
    }

    /*
     * Starting the measuring.
     */
    auto mean = static_cast<double>(initNodes);
    double balance = 0;

    for (uint32_t i = 0; i < initNodes; i++) {
        if (absorbedKeys[i] > 0) {
            if (balance < (absorbedKeys[i] / mean)) {
                balance = absorbedKeys[i] / mean;
            }
        } else {
            cerr << "# [ERR] ----- Unable to process the node: " << i << "." << endl;
        }
    }

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ balance = " << balance << endl;
    return balance;
}
