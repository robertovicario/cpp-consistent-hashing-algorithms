/**
 * @author Amos Brocco, Roberto Vicario
 */

#pragma once

#include <iostream>
#include <random>

using namespace std;

static unsigned long allocations{0};
static unsigned long deallocations{0};
static unsigned long allocated{0};
static unsigned long deallocated{0};
static unsigned long maximum{0};

void *operator new(size_t size) {
    void *p = malloc(size);
    if (p) {
        allocations += 1;
        allocated += size;
        maximum = allocated > maximum ? allocated : maximum;
    }

    return p;
}

void *operator new[](size_t size) {
    void *p = malloc(size);
    if (p) {
        allocations += 1;
        allocated += size;
        maximum = allocated > maximum ? allocated : maximum;
    }

    return p;
}

void operator delete(void *ptr) noexcept {
    deallocations += 1;
    free(ptr);
}

void operator delete[](void *ptr) noexcept {
    deallocations += 1;
    free(ptr);
}

void operator delete(void *ptr, std::size_t size) noexcept {
    deallocations += 1;
    deallocated += size;
    free(ptr);
}

void operator delete[](void *ptr, std::size_t size) noexcept {
    deallocations += 1;
    deallocated += size;
    free(ptr);
}

void resetMemoryUsage() noexcept {
    allocations = 0;
    deallocations = 0;
    allocated = 0;
    deallocated = 0;
    maximum = 0;
}

long getMemoryUsage() {
    return allocated;
}

template <typename Engine, typename... Args>
long computeMemoryUsage(const YAML::Node& yaml, const string& algorithm, uint32_t initNodes, Args... args) {
    /*
     * Starting the measuring.
     */
    long initialMemory = getMemoryUsage();

    auto* bucket_status = new uint32_t[initNodes]();
    for (uint32_t i = 0; i < initNodes; i++) {
        bucket_status[i] = 1;
    }

    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

    /*
     * Selecting the percentage of nodes to remove.
     */
    auto numRemovals = static_cast<uint32_t>(initNodes * 0.1);
    for (int i = 0; i < numRemovals;) {
        uint32_t removed = rand() % initNodes;
        if (bucket_status[removed] == 1) {
            auto rnode = engine.removeBucket(removed);
            bucket_status[rnode] = 0;
            i++;
        }
    }

    long finalMemory = getMemoryUsage();
    resetMemoryUsage();

    long memoryUsage = finalMemory - initialMemory;

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ memory_usage = " << memoryUsage << " B" << endl;
    return memoryUsage;
}
