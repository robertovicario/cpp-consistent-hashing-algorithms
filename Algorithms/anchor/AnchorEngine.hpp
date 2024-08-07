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

#include "AnchorHash.hpp"

class AnchorEngine final {
private:
    AnchorHash anchor;

public:
    AnchorEngine(uint32_t anchor_set, uint32_t working_set)
        : anchor{working_set * anchor_set, anchor_set}
    {}

    /**
   * Returns the bucket where the given key should be mapped.
   * This version uses the same hash function as Anchor
   *
   * @param key the key to map
   * @param seed the initial seed for CRC32c
   * @return the related bucket
   */
    uint32_t getBucketCRC32c(uint64_t key, uint64_t seed) noexcept
    {
        return anchor.ComputeBucket(key, seed);
    }

    /**
   * Adds a new bucket to the engine.
   *
   * @return the added bucket
   */
    uint32_t addBucket() noexcept { return anchor.UpdateNewBucket(); }

    /**
   * Removes the given bucket from the engine.
   *
   * @param bucket the bucket to remove
   * @return the removed bucket
   */
    uint32_t removeBucket(uint32_t bucket) noexcept
    {
        anchor.UpdateRemoval(bucket);
        return bucket;
    }
};
