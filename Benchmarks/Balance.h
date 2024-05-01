/**
 * @author Amos Brocco
 * @author Roberto Vicario
 */

#pragma once

#include <iostream>
#include <random>

using namespace std;

template <typename Algorithm>
double computeBalance(string algorithm, uint32_t anchor_set,
                uint32_t working_set, uint32_t num_removals,
                uint32_t num_keys) {
    Algorithm engine(anchor_set, working_set);

    /**
     * Selecting random bucket index.
     */
    random_device rd;
    mt19937 rng(rd());

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
     * Starting measuring.
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

    /**
     * Printing results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ balance        = " << balance << endl;

    return balance;
}
