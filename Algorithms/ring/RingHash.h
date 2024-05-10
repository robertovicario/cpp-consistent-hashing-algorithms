/**
 * @author Roberto Vicario
*/

#pragma once

#include <cstdint>
#include <map>
#include <stack>
#include "../../../../../../Downloads/cpp-consistent-hashing-algorithms-ring/Algorithms/misc/ConsistentHash.hpp"

class RingHash : public ConsistentHash {
private:
    std::map<uint32_t, uint32_t> workSet;
    uint32_t V;
    std::stack<uint32_t> failedSet;
    const char *name = "RingHash";

    void insert(uint32_t nodeID);

public:
    RingHash(uint32_t, uint32_t);
    ~RingHash() = default;

    uint32_t getSize();
    void updateRemoval(uint32_t index);
    uint32_t updateAddition();
    uint32_t getNodeID(uint32_t key, uint32_t* numHash);
    inline const char* getName() {
        return name;
    }
};
