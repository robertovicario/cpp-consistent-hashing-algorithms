/*
 * Copyright (c) 2023 Amos Brocco.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <cstdint>
#include "../misc/HashFunctions.hpp"

class JumpEngine final {
private:
    uint32_t initNodes;

public:
    explicit JumpEngine(uint32_t initNodes) : initNodes{initNodes}
    {}

    /**
   * Returns the bucket where the given key should be mapped.
   * This implementations is the same as provided by Jump authors
   *
   * @param key the key to map
   * @param seed the initial seed for CRC32c
   * @return the related bucket
   */
    uint32_t getBucketCRC32c(uint64_t key, uint64_t seed) {
        uint64_t hash = crc32(key, seed);
        int64_t b = 1, j = 0;

        while (j < initNodes) {
            b = j;
            hash = hash * 2862933555777941757ULL + 1;
            j = (b + 1) * (double(1LL << 31) / double((hash >> 33) + 1));
        }

        return b;
    }

    /**
   * Adds a new bucket to the engine.
   *
   * @return the added bucket
   */
    uint32_t addBucket() noexcept { return initNodes++; }

    /**
   * Removes the given bucket from the engine.
   * Since Jump does not support random removals, it will always remove the
   * last bucket.
   *
   * @return the removed bucket
   */
    uint32_t removeBucket(uint32_t index) {
        return --initNodes;
    }
};
