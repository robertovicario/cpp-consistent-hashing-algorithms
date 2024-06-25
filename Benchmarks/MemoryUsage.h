/**
 * @author Roberto Vicario
 */

#pragma once

#include <iostream>

using namespace std;

double totalAllocated = 0;
double totalFreed = 0;

void* operator new(size_t size) {
    totalAllocated += size;
    return malloc(size);
}

void operator delete(void* ptr) noexcept {
    free(ptr);
}

void* operator new[](size_t size) {
    totalAllocated += size;
    return malloc(size);
}

void operator delete[](void* ptr) noexcept {
    free(ptr);
}

double getAllocatedMemory() {
    return totalAllocated - totalFreed;
}

template <typename Engine>
double computeMemoryUsage(const string& algorithm, uint32_t initNodes) {
    /*
     * Initializing the engine.
     */
    double initalMemory = getAllocatedMemory();
    Engine engine(initNodes);

    /*
     * Starting the measuring.
     */
    double finalMemory = getAllocatedMemory();
    double size = finalMemory - initalMemory;

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ memory_usage = " << size << " B" << endl;
    return size;
}
