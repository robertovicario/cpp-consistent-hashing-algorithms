/**
 * @copyright Roberto Vicario (C) 2024
 */

#pragma once

#include "DxHash.h"
#include "../misc/HashFunctions.h"

DxHash::DxHash(uint32_t n_working): num_working(n_working), size(1), nodes(){
    uint32_t w_size = (num_working >> 1), i = 0;
    while(w_size){
        size <<= 1;
        w_size >>= 1;
    }

    if(num_working > size){
        size <<= 1;
    }

    nodes.resize(size);
    // nodes = new uint8_t[size]();
    // nodes.setBitSize(size);

    for(i = 0; i < num_working; i++){
        nodes[i] = 1;
    }

    for(i = num_working; i < size; i++){
        nodes[i] = 0;
    }
}

DxHash::DxHash(uint32_t n_total, uint32_t n_working): size(n_total), num_working(n_working), nodes(){
    nodes.resize(size);

    uint32_t i;
    for(i = 0; i < num_working; i++){
        nodes[i] = 1;
    }

    for(i = num_working; i < size; i++){
        nodes[i] = 0;
    }
}


uint32_t DxHash::getSize(){
    return size;
}

uint32_t DxHash::getOfflineSize(){
    return size - num_working;
}


void DxHash::resize(){
    int new_size = 1;
    while (new_size <= num_working){
        new_size = new_size << 1;
    }

    if(new_size >= size) { // scale
        nodes.resize(new_size, 0);
    }

    int num_insertion = 0;
    if(new_size < size) { // shrink
        for(uint32_t i = new_size; i < size; i++){
            if(nodes[i] == 1){
                num_insertion++;
            }
        }
        nodes.resize(new_size, 0);
        for(uint32_t i = 0; i < new_size; i++){
            if(num_insertion > 0 && nodes[i] == 0){
                nodes[i] = 1;
                num_insertion--;
            }
        }
    }
    size = new_size;
}



void DxHash::updateRemoval(uint32_t index){
    auto nodeID = nodes[index];
    if(nodeID){
        nodes[index] = 0;
        num_working --;
    }
    else{
        return;
    }
}

uint32_t DxHash::updateAddition(){
    if(num_working == size)
        resize();
    uint32_t index = getInactiveNodeID(1228);
    nodes[index] = 1;
    num_working ++;
    return index;
}

uint32_t DxHash::getInactiveNodeID(uint32_t key){
    uint32_t key2 = generate32RandomNumber(key);
    uint32_t bs = crc32c_sse42_u64(key, key2);
    uint32_t index = bs % size;
    uint32_t i = 1;
    while(nodes[index]){
        bs = crc32c_sse42_u64(bs, key2);
        index = bs % size;
        i += 1;
        if (i >= 4 * size){
            return -1;
        }
    };
    return index;
}

uint32_t DxHash::getNodeID(uint32_t key, uint32_t* numHash){
    uint32_t key2 = generate32RandomNumber(key);
    uint32_t bs = crc32c_sse42_u64(key, key2);
    uint32_t index = bs % size;
    uint32_t i = 1;
    while(!nodes[index]){
        bs = crc32c_sse42_u64(bs, key2);
        index = bs % size;
        i += 1;
        if (i >= 4 * size){
            return -1;
        }
    };
    *numHash = i;

    return index;
}
