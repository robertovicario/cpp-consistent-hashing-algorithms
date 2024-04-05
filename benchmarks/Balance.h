/**
 * @author Amos Brocco
 * @author Roberto Vicario
 */

#include <iostream>
#include <random>

using namespace std;

/**
 * Computes the balance of a given algorithm.
 *
 * @tparam Algorithm Type of algorithm to compute balance for.
 * @param algorithm Name or identifier of the algorithm.
 * @param anchor_set Size of the anchor set.
 * @param working_set Size of the working set.
 * @param num_removals Number of removals from the working set.
 * @param num_keys Number of keys to absorb into the anchor set.
 * @return 0 if successful.
 */
template <typename Algorithm>
int computeBalance(string algorithm, uint32_t anchor_set,
                uint32_t working_set, uint32_t num_removals,
                uint32_t num_keys) {
    Algorithm engine(anchor_set, working_set);
    random_device rd;
    mt19937 rng(rd());
    
    /**
     * Selecting randomly bucket to remove.
     */
    vector<uint32_t> bucket_status(working_set, 1);
    int i = 0;
    
    while (i < num_removals) {
        uint32_t index = rng() % working_set;
        if (bucket_status[index] == 1) {
            auto removed_node = engine.removeBucket(index);
            bucket_status[removed_node] = 0;
            i++;
        }
    }

    /**
     * Absorbing keys into anchor set.
     */
    vector<uint32_t> absorbed_keys(anchor_set, 0);
    for (i = 0; i < num_keys; i++) {
        absorbed_keys[engine.getBucketCRC32c(rng(), rng())] += 1;
    }

    /**
     * Computing balance.
     */
    double mean = static_cast<double>(num_keys) / (working_set - num_removals);
    double balance = 0;

    for (i = 0; i < anchor_set; i++) {
        if (bucket_status[i]) {
            if (balance < (absorbed_keys[i] / mean)) {
                balance = absorbed_keys[i] / mean;
            }
        } else if (0 < absorbed_keys[i]) {
            cerr << "# [ERR] ----- There was an error processing node " << i << "." <<endl;
        }
    }

    cout << "# [LOG] ----- @" << algorithm << "\t>_ balance        = " << balance << endl;

    return 0;
}
