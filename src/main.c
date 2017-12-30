#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "gf_operations.h"
#include "key_schedule.h"


void print_byte_arr(const byte *a, size_t n, size_t row_size) {
    for (size_t i = 0; i < n; ++i) {
        printf("%02x ", a[i]);
        if ((i + 1) % row_size == 0) {
            printf("\n");
        }
    }
    printf("\n");
}

static inline void print_word(word a) {
    printf("%02x %02x %02x %02x\n", byte_at(a, 0), byte_at(a, 1), byte_at(a, 2), byte_at(a, 3));
}

void print_word_arr(const word *a, size_t n, size_t row_size) {
    for (size_t i = 0; i < n; ++i) {
        word w = a[i];
        printf("%02x %02x %02x %02x ", byte_at(w, 0), byte_at(w, 1), byte_at(w, 2), byte_at(w, 3));
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

int main() {

    char *key_string = "603DEB1015CA71BE2B73AEF0857D77811F352C073B6108D72D9810A30914DFF4";
    printf("%ld\n", strlen(key_string));

    byte key[32] = {0}; /* = {
            0x60, 0x15, 0x2B, 0x85, 0x1F, 0x3B, 0x2D, 0x09,
            0x3D, 0xCA, 0x73, 0x7D, 0x35, 0x61, 0x98, 0x14,
            0xEB, 0x71, 0xAE, 0x77, 0x2C, 0x08, 0x10, 0xDF,
            0x10, 0xBE, 0xF0, 0x81, 0x07, 0xD7, 0xA3, 0xF4
    };*/
    key_string_to_bytes(key_string, key);
    key_string_to_bytes(key_string, key);
    print_byte_arr(key, 32, 16);

    word expanded_key[60];
    key_schedule(key, expanded_key);
    print_word_arr(expanded_key, 60, 4);
    return 0;
}