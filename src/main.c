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

    byte *key = malloc(32 * sizeof(byte));
    key_string_to_bytes(key_string, key);

    print_byte_arr(key, 32, 16);

    word *expanded_key = malloc(60 * sizeof(word));
    key_schedule(key, expanded_key);
    print_word_arr(expanded_key, 60, 4);

    print_word(expanded_key[0], true);
    printf("\n");


    char *plaintext_string = "6BC1BEE22E409F96E93D7E117393172A";
    byte *pt = malloc(16 * sizeof(byte));
    key_string_to_bytes(plaintext_string, pt);

    word *s = (word *) pt;
    print_state(s);

    print_word(expanded_key[0], true);

    printf("\n");
    encrypt(s, expanded_key);


    word state[] = {0x03020100, 0x07060504, 0x0b0a0908, 0x0f0e0d0c};

    return 0;
}