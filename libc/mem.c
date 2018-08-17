//
// Created by harrisonturton on 17/08/18.
//

#include "mem.h"

void memory_copy(uint8_t *source, uint8_t *dest, uint32_t nbytes) {
    uint32_t i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memory_set(uint8_t *dest, uint8_t val, uint32_t len) {
    uint8_t *temp = (uint8_t *) dest;
    for (; len != 0; len--) *temp++ = val;
}
