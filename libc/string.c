//
// Created by harrisonturton on 17/08/18.
//

#include "string.h"

uint32_t strlen(uint8_t s[]) {
    uint32_t i = 0;
    while (s[i] != '\0') ++i;
    return i;
}

void reverse(uint8_t s[]) {
    uint32_t c, i, j;
    for (i = 0, j = strlen(s)-1; i < j; i++, j--) {
        c = s[i];
        s[i] = s[j];
        s[j] = c;
    }
}

void int_to_ascii(uint32_t n, uint8_t str[]) {
    uint32_t i, sign;
    if ((sign = n) < 0) n = -n;
    i = 0;
    do {
        str[i++] = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0) str[i++] = '-';
    str[i] = '\0';

    reverse(str);
}

void append(uint8_t s[], uint8_t n) {
    int len = strlen(s);
    s[len] = n;
    s[len+1] = '\0';
}

void backspace(uint8_t s[]) {
    int len = strlen(s);
    s[len - 1] = '\0';
}

uint8_t strcmp(uint8_t s_a[], uint8_t s_b[]) {
    int i;
    for (i = 0; s_a[i] == s_b[i]; i++) {
        if (s_a[i] == '\0') return 0;
    }
    return s_a[i] - s_b[i];
}
