/**
 * @author Amos Brocco, Roberto Vicario
 */

#pragma once

#include <iostream>

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

double getMemoryUsage() {
    return static_cast<double>(allocated);
}

template <typename Engine, typename... Args>
double computeMemoryUsage(const YAML::Node& yaml, const string& algorithm, uint32_t initNodes, Args... args) {
    /*
     * Starting the measuring.
     */
    double initialMemory = getMemoryUsage();

    /*
     * Initializing the engine.
     */
    Engine engine(initNodes, args...);

    double finalMemory = getMemoryUsage();
    double memoryUsage = finalMemory - initialMemory;

    /*
     * Returning the results.
     */
    cout << "# [LOG] ----- @" << algorithm << "\t>_ memory_usage = " << memoryUsage << " B" << endl;
    return memoryUsage;
}
