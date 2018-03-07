#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "gf_operations.h"
#include "key_schedule.h"
#include "cypher.h"
#include "print_debug.h"
#include "inverse.h"
#include "cbc.h"

#define N 32

extern inline void print_word(word a, bool newl);

int main() {
    char *key_string = "603DEB1015CA71BE2B73AEF0857D77811F352C073B6108D72D9810A30914DFF4";
    printf("%u \n", strlen(key_string));

    byte *key = malloc(32 * sizeof(byte));
    hex_string_to_bytes(key_string, key, 32);

    print_byte_arr(key, 32, 16);

    word *expanded_key = malloc(60 * sizeof(word));
    key_schedule(key, expanded_key);
    print_word_arr(expanded_key, 60, 4);

    char *iv_string = "16161616161616161616161616161616";
    byte *iv = malloc(16 * sizeof(byte));
    hex_string_to_bytes(iv_string, iv, 16);

    char *pt_string = "64646464646464646464646464646464646464646464646464646464646464646464646464646464646464646464646464646464646464646464646464646464";
    size_t pt_size = 64;
    byte *pt = malloc(pt_size * sizeof(byte));
    hex_string_to_bytes(pt_string, pt, pt_size);

    cbc_encrypt((word *) pt, expanded_key, (word *) iv, pt_size);
    print_byte_arr(pt, pt_size, 16);

    cbc_decrypt((word *)pt, expanded_key, (word *) iv, pt_size);
    print_byte_arr(pt, pt_size, 16);

    printf("%d\n", encrypt_file("to_encrypt.txt", "encrypted.txt", expanded_key, (word *)iv));
    printf("%d\n", decrypt_file("encrypted.txt", "decrypted.txt", expanded_key, (word *)iv));
    return 0;
}