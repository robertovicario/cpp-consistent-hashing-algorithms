/**
 * @author Roberto Vicario
 */

#pragma once

#include "DxHash.hpp"

class DxEngine {
private:
    DxHash dx;

public:
    DxEngine(uint32_t n_total, uint32_t n_working) : dx{n_total, n_working} {}
    uint32_t getBucketCRC32c(uint32_t key, uint32_t seed) { return dx.getNodeID(key, &seed); }
    uint32_t addBucket() { return dx.updateAddition(); }
    uint32_t removeBucket(uint32_t bucket) {
        dx.updateRemoval(bucket);
        return bucket;
    }
};
