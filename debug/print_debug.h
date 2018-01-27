//
// Created by Noam on 31/12/2017.
//

#ifndef AES_PRINT_DEBUG_H
#define AES_PRINT_DEBUG_H


#include <stdlib.h>
#include <stdbool.h>
#include "stdio.h"
#include "gf_operations.h"
#include "key_schedule.h"

#define N 32

#define debug_print(fmt, ...) \
            do { if (DEBUG) printf(fmt, ##__VA_ARGS__); } while (0)

#define debug_print_state(s) \
            do { if (DEBUG) print_state(s); } while (0)

void print_byte_arr(const byte *a, size_t n, size_t row_size);

void print_word_arr(const word *a, size_t n, size_t row_size);

inline void print_word(word a, bool newl) {
    byte *p = (byte *) (&a);
    for (int i = 0; i < 4; ++i) {
        printf("%02x ", p[i]);
    }
    if (newl)
        printf("\n");
}

void print_state(word s[]);

void key_string_to_bytes(const char str[N * 2], byte key[N]);

#endif //AES_PRINT_DEBUG_H
