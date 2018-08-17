//
// Created by harrisonturton on 17/08/18.
//

#ifndef SIMPLE_KERNEL_STRING_H
#define SIMPLE_KERNEL_STRING_H

#include <stdint.h>

void int_to_ascii(uint32_t n, uint8_t str[]);
uint32_t strlen(uint8_t s[]);
void append(uint8_t s[], uint8_t n);
void backspace(uint8_t s[]);

#endif //SIMPLE_KERNEL_STRING_H
