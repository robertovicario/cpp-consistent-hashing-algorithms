/**
 * @authors Amos Brocco, Roberto Vicario
*/

#pragma once

static inline uint32_t crc32c(uint32_t key, uint32_t seed) {
    #ifdef __x86_64
        __asm__ volatile("crc32q %[key], %[seed];"
                        : [seed] "+r"(seed)
                        : [key] "rm"(key));
        return seed;
    #elif __aarch64__
        uint32_t crc = 0xFFFFFFFF;

        __asm__ volatile(
            "crc32cx %w0, %w0, %x1"
            : "+r" (crc)
            : "r" (key));

        return crc ^ seed;
    #endif
}

static uint32_t generate32RandomNumber(uint32_t key) {
    return (key*421757ULL+1);
}
