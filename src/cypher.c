//
// Created by Noam on 31/12/2017.
//

#include "cypher.h"
#include "print_debug.h"


// the sub_bytes stage
void sub_bytes(word s[4]) {
    for (int i = 0; i < 4; ++i) {
        s[i] = sub_word(s[i]);
    }
}

// rotate w left by i bytes
static inline word rotate_left(word w, int i) {
    return w >> 8 * i | w << 8 * (4 - i);
}

// the shift_rows stage
void shift_rows(word s[4]) {
    for (int i = 1; i < 4; ++i) {
        s[i] = rotate_left(s[i], i);
    }
}

// the add_round_key stage
void add_round_key(word state[4], const word key[4]) {
    for (int i = 0; i < 4; ++i) {
        state[i] ^= key[i];
    }
}

const byte mix_col_mat[4][4] = {{2, 3, 1, 1},
                                {1, 2, 3, 1},
                                {1, 1, 2, 3},
                                {3, 1, 1, 2}};

void mix_columns(word state[4]) {
    byte *mat = (byte *) (&state);
    // initialize to 0
    byte new_state[4 * 4] = {0};
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            new_state[i + 4 * j] ^= mul(mix_col_mat[i][j], mat[i + 4 * j]);
        }
    }
    for (int i = 0; i < 4; ++i) {
        state[i] = ((word *) new_state)[4 * i];
    }
}