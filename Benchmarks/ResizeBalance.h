#include <iostream>
#include <random>
#include <yaml-cpp/yaml.h>
#include <vector>

using namespace std;

template <typename Engine, typename... Args>
double computeResizeBalance(const YAML::Node& yaml, const string& algorithm, u_int32_t initNodes, Args... args) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

    /*
     * Checking the configuration.
     */
    int keyMultiplier = 100;
    if (yaml["benchmarks"] && yaml["benchmarks"]["name"] && yaml["benchmarks"]["name"]["resize-balance"]) {
        if (yaml["benchmarks"]["name"]["resize-balance"]["args"]) {
            auto configs = yaml["benchmarks"]["name"]["resize-balance"]["args"];
            if (configs["keyMultiplier"]) {
                keyMultiplier = configs["keyMultiplier"].as<int>(100);
            }
        }
    }

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
     * Starting the measuring.
     */
    vector<uint32_t> absorbed_keys(initNodes * keyMultiplier, 0);
    for (i = 0; i < initNodes; i++) {
        uint32_t bucketIndex = engine.getBucketCRC32c(rng(), rng()) % (initNodes * keyMultiplier);
        absorbed_keys[bucketIndex] += 1;
    }

    double mean = static_cast<double>(initNodes) / (initNodes - numRemovals);
    double balance = 0;

    for (i = 0; i < initNodes; i++) {
        if (bucket_status[i]) {
            if (balance < (absorbed_keys[i * keyMultiplier] / mean)) {
                balance = absorbed_keys[i * keyMultiplier] / mean;
            }
        }
    }

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ resize_balance = " << balance << endl;
    return balance;
}
