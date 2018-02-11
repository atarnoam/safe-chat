//
// Created by Rami on 26/01/2018.
//

#include <assert.h>
#include "inverse.h"

// rotate w left by i bytes
static inline word rotate_right(word w, int i) {
    return w << 8 * i | w >> 8 * (4 - i);
}

// the inv_shift_rows stage, this is actually a shift columns
void inv_shift_rows(word s[4]) {
    transpose(s);
    for (int i = 1; i < 4; ++i) {
        s[i] = rotate_right(s[i], i);
    }
    transpose(s);
}

// Applies s_box to all four bytes in the word
word inv_sub_word(word w) {
    byte *p = ((byte *) (&w));
    for (int i = 0; i < 4; ++i) {
        p[i] = inv_s_box(p[i]);
    }
    return *((word *) p);
}

// the sub_bytes stage
void inv_sub_bytes(word s[4]) {
    for (int i = 0; i < 4; ++i) {
        s[i] = inv_sub_word(s[i]);
    }
}

void inv_mix_column(byte *r) {
    byte a[4];
    byte c;
    for (c = 0; c < 4; c++) {
        a[c] = r[c];
    }
    // This is less nice than mix_column
    r[0] = mul(a[0], 14) ^ mul(a[3], 9) ^ mul(a[2], 13) ^ mul(a[1], 11);
    r[1] = mul(a[1], 14) ^ mul(a[0], 9) ^ mul(a[3], 13) ^ mul(a[2], 11);
    r[2] = mul(a[2], 14) ^ mul(a[1], 9) ^ mul(a[0], 13) ^ mul(a[3], 11);
    r[3] = mul(a[3], 14) ^ mul(a[2], 9) ^ mul(a[1], 13) ^ mul(a[0], 11);
}

// the mix_columns stage
void inv_mix_columns(word state[4]) {
    for (int i = 0; i < 4; ++i) {
        inv_mix_column((byte *) (state + i));
    }
}

// decrypts ciphertext, uses expanded key.
void decrypt(word ciphertext[4], const word expanded_key[]) {
    const word *curr_key = expanded_key + 4 * 59;
    add_round_key(ciphertext, curr_key);
    curr_key -= 4;
    for (int i = 13; i >= 1; --i, curr_key -= 4) {
        inv_shift_rows(ciphertext);
        inv_sub_bytes(ciphertext);
        add_round_key(ciphertext, curr_key);
        inv_mix_columns(ciphertext);
    }
    inv_shift_rows(ciphertext);
    inv_sub_bytes(ciphertext);
    add_round_key(ciphertext, curr_key);
}
