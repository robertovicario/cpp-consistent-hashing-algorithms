/**
 * @file ConsistentHash.hpp
 * @brief Header file for ConsistentHash class.
 * @author Roberto Vicario
 */

#pragma once

class ConsistentHash {
public:
    virtual uint32_t getNodeID(uint32_t key, uint32_t* numHash) = 0;
    virtual uint32_t updateAddition() = 0;
    virtual void updateRemoval(uint32_t index) = 0;
};
