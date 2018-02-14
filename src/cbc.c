//
// Created by Rami on 14/02/2018.
//

#include "cbc.h"

// a, b are 16 bytes long. does a = a ^ b.
void xor_mem(word *a, const word *b) {
    for (int i = 0; i < 4; ++i) {
        *a ^= *b;
        a++, b++;
    }
}

//pt_length is in bytes
//for now we suppose pt_length % 16 == 0
void cbc_encrypt(word *plaintext, const word *expanded_key, const word *iv, size_t pt_length) {
    size_t num_of_rounds = pt_length / 16;
    const word *prev = iv;
    for (int i = 0; i < num_of_rounds; ++i) {
        xor_mem(plaintext, prev);
        encrypt(plaintext, expanded_key);
        prev = plaintext;
        plaintext += 4;
    }
}