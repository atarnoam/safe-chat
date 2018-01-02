#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gf_operations.h"
#include "key_schedule.h"
#include "cypher.h"
#include "print_debug.h"

#define N 32

extern inline void print_word(word a, bool newl);

int main() {
    char *key_string = "603DEB1015CA71BE2B73AEF0857D77811F352C073B6108D72D9810A30914DFF4";
    printf("%ld\n", strlen(key_string));

    byte key[32] = {0};
    key_string_to_bytes(key_string, key);

    print_byte_arr(key, 32, 16);

    word expanded_key[60];
    key_schedule(key, expanded_key);
    print_word_arr(expanded_key, 60, 4);

    word s[] = {0x00010203, 0x04050607, 0x08090a0b, 0x0c0d0e0f};
    print_state(s);

    printf("\n");
    //shift_rows(s);
    //print_state(s);

    byte mat[4][4];
    to_matrix(s, mat);

    for (int i = 0; i < 4; ++i) {
        print_byte_arr(mat[i], 4, 60);
    }

    return 0;
}