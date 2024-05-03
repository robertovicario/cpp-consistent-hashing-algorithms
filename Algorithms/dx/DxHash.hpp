/**
 * @author Roberto Vicario
 */

#pragma once

#include <cstdio>

#include "../misc/ConsistentHash.hpp"
#include "../misc/HashFunctions.h"

class DxHash : public ConsistentHash {
private:
    std::vector<bool> nodes;
    uint32_t num_working{};
    uint32_t size{};

public:
    DxHash(uint32_t initNodes) : size(initNodes), num_working(initNodes), nodes() {
        nodes.resize(size);

        uint32_t i;
        for (i = 0; i < num_working; i++) {
            nodes[i] = true;
        }

        for (i = num_working; i < size; i++) {
            nodes[i] = false;
        }
    }

    uint32_t getNodeID(uint32_t key, uint32_t *numHash) override {
        uint32_t key2 = generate32RandomNumber(key);
        uint32_t bs = crc32(key, key2);
        uint32_t index = bs % size;
        uint32_t max_attempts = 4 * size;
        uint32_t i = 1;

        while (!nodes[index]) {
            bs = crc32(bs, key2);
            index = bs % size;
            i++;
            if (i >= max_attempts) {
                *numHash = i;
                return -1;
            }
        }

        *numHash = i;
        return index;
    }

    uint32_t getInactiveNodeID(uint32_t key) {
        uint32_t key2 = generate32RandomNumber(key);
        uint32_t bs = crc32(key, key2);
        uint32_t index = bs % size;
        uint32_t i = 1;
        while (nodes[index]) {
            bs = crc32(bs, key2);
            index = bs % size;
            i += 1;
            if (i >= 4 * size) {
                return -1;
            }
        }
        return index;
    }

    void updateRemoval(uint32_t index) override {
        auto nodeID = nodes[index];
        if (nodeID) {
            nodes[index] = false;
            num_working--;
        } else {
            return;
        }
    }

    void resize() {
        int new_size = 1;
        while (new_size <= num_working) {
            new_size = new_size << 1;
        }

        if (new_size >= size) { // scale
            nodes.resize(new_size, false);
        }

        int num_insertion = 0;
        if (new_size < size) { // shrink
            for (uint32_t i = new_size; i < size; i++) {
                if (nodes[i] == 1) {
                    num_insertion++;
                }
            }
            nodes.resize(new_size, false);
            for (uint32_t i = 0; i < new_size; i++) {
                if (num_insertion > 0 && nodes[i] == 0) {
                    nodes[i] = true;
                    num_insertion--;
                }
            }
        }
        size = new_size;
    }

    uint32_t updateAddition() override {
        if (num_working == size)
            resize();
        uint32_t index = getInactiveNodeID(1228);
        nodes[index] = true;
        num_working++;
        return index;
    }
};