/**
 * @author Roberto Vicario
 */

#pragma once

#include <iostream>

using namespace std;

template <typename Engine>
double computeMemoryUsage(const string& algorithm, uint32_t initNodes) {
    /*
     * Initializing the engine.
     */
    Engine engine(initNodes);

    /*
     * Starting the measuring.
     */
    double staticMemory = sizeof(engine);
    double dynamicMemory = sizeof(engine.getMemoryUsage());
    double size = staticMemory + dynamicMemory;

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ memory_usage = " << size << " B" << endl;
    return size;
}
