//
// Created by harrisonturton on 17/08/18.
//

#ifndef SIMPLE_KERNEL_MEM_H
#define SIMPLE_KERNEL_MEM_H

#include <stdint.h>

void memory_copy(uint8_t *source, uint8_t *dest, uint32_t nbytes);
void memory_set(uint8_t *dest, uint8_t val, uint32_t len);

#endif //SIMPLE_KERNEL_MEM_H
