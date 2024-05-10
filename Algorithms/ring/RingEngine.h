/**
 * @author Roberto Vicario
*/

#pragma once

#include <cstdint>
#include "RingHash.cpp"

class RingEngine final {
private:
    RingHash ring;

public:
    RingEngine(uint32_t initNodes)
            : ring{initNodes, initNodes} {}

    uint32_t getBucketCRC32c(uint32_t key, uint32_t seed) noexcept { return ring.getNodeID(key, &seed); }

    uint32_t addBucket() noexcept { return ring.updateAddition(); }

    uint32_t removeBucket(uint32_t bucket) noexcept {
        ring.updateRemoval(bucket);
        return bucket;
    }
};
