//
// Created by Noam on 31/12/2017.
//

#include "print_debug.h"

void print_byte_arr(const byte *a, size_t n, size_t row_size) {
    for (size_t i = 0; i < n; ++i) {
        printf("%02x ", a[i]);
        if ((i + 1) % row_size == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void print_state(word s[]) {
    for (int i = 0; i < 4; ++i) {
        print_word(s[i], true);
    }
}

void print_word_arr(const word *a, size_t n, size_t row_size) {
    for (size_t i = 0; i < n; ++i) {
        word w = a[i];
        print_word(w, false);
        if ((i + 1) % row_size == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

void key_string_to_bytes(const char str[N * 2], byte key[N]) {
    for (int i = 0; i < 2 * N; i += 2) {
        char temp[] = {str[i], str[i + 1], '\0'};
        key[i / 2] = (byte) strtol(temp, NULL, 16);
    }
}
