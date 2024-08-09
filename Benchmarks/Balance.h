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
     * Checking the configuration.
     */
    int keyMultiplier = 100;
    if (yaml["benchmarks"] && yaml["benchmarks"]["name"] && yaml["benchmarks"]["name"]["balance"]) {
        if (yaml["benchmarks"]["name"]["balance"]["args"]) {
            auto configs = yaml["benchmarks"]["name"]["balance"]["args"];
            if (configs["keyMultiplier"]) {
                keyMultiplier = configs["keyMultiplier"].as<int>(100);
            }
        }
    }

    /*
     * Starting the measuring.
     */
    random_device rd;
    mt19937 rng(rd());
    size_t numKeys = initNodes * keyMultiplier;
    vector<uint32_t> absorbed_keys(initNodes, 0);

    for (size_t i = 0; i < numKeys; i++) {
        uint32_t bucket = engine.getBucketCRC32c(rng(), rng());
        absorbed_keys[bucket] += 1;
    }

    double mean = static_cast<double>(numKeys) / initNodes;
    double balance = 0;
    vector<uint32_t> bucket_status(initNodes, 1);

    for (size_t i = 0; i < initNodes; i++) {
        if (bucket_status[i]) {
            if (balance < (absorbed_keys[i] / mean)) {
                balance = absorbed_keys[i] / mean;
            }
        }
    }

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ balance = " << balance << endl;
    return balance;
}
