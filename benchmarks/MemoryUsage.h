/**
 * @author Roberto Vicario
 */

#pragma once

#include <iostream>
using namespace std;

template <typename Algorithm>
int computeMemoryUsage(string algorithm, uint32_t anchor_set, uint32_t working_set) {
    Algorithm engine(anchor_set, working_set);
    size_t size = sizeof(engine);
    cout << "# [LOG] ----- @" << algorithm << "\t>_ memory_usage   = " << size << " bytes" << endl;

    return 0;
}
