/**
 * @author Roberto Vicario
 */

#pragma once

class ConsistentHash {
public:
    virtual uint32_t getNodeID(uint32_t key, uint32_t* seed) = 0;
    virtual uint32_t updateAddition() = 0;
    virtual void updateRemoval(uint32_t index) = 0;
};
