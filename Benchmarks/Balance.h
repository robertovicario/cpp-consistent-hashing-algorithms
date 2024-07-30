/**
 * @authors Amos Brocco, Roberto Vicario
 */

#include <iostream>
#include <random>

using namespace std;

template <typename Engine, typename... Args>
double computeBalance(const YAML::Node& yaml, const string& algorithm, u_int32_t initNodes, Args... args) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

    /*
     * Starting the measuring.
     */
    random_device rd;
    mt19937 rng(rd());
    vector<uint32_t> absorbed_keys(initNodes, 0);

    for (int i = 0; i < initNodes; i++) {
        absorbed_keys[engine.getBucketCRC32c(rng(), rng())] += 1;
    }

    double mean = static_cast<double>(initNodes) / initNodes;
    double balance = 0;
    vector<uint32_t> bucket_status(initNodes, 1);

    for (int i = 0; i < initNodes; i++) {
        if (bucket_status[i]) {
            if (balance < (absorbed_keys[i] / mean)) {
                balance = absorbed_keys[i] / mean;
            }
        } else if (0 < absorbed_keys[i]) {
            cout << "# [ERR] ----- Unable to process the node: " << i << "." << endl;
        }
    }

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ balance = " << balance << endl;
    return balance;
}
