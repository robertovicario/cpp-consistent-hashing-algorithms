/**
 * @author Roberto Vicario
*/

#pragma once

#include "MaglevHash.cpp"

class MaglevEngine final {
private:
    MaglevHash maglev;

public:
    MaglevEngine(uint32_t initNodes) : maglev{initNodes, initNodes}{}
    uint32_t getBucketCRC32c(uint32_t key, uint32_t seed) noexcept { return maglev.getNodeID(key, &seed); }
    uint32_t addBucket() noexcept { return maglev.updateAddition(); }
    uint32_t removeBucket(uint32_t bucket) noexcept {
        maglev.updateRemoval(bucket);
        return bucket;
    }
};
