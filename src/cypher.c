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

const byte mix_col_mat[4][4] = {{0x02, 0x03, 0x01, 0x01},
                                {0x01, 0x02, 0x03, 0x01},
                                {0x01, 0x01, 0x02, 0x03},
                                {0x03, 0x01, 0x01, 0x02}};

void mix_columns(word state[4]) {
    // this is actually a 4x4 matrix, note that "mat[i][j]" is mat[4*i + j].
    byte *mat = (byte *) state;
    // initialize to 0.
    byte new_state[4 * 4] = {0};

    // multiply mix_col_mat by mat.
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            for (int k = 0; k < 4; ++k) {
                new_state[4 * i + j] ^= mul(mix_col_mat[i][k], mat[4 * k + j]);
            }
        }
    }
    for (int i = 0; i < 4; ++i) {
        state[i] = *(word *) (new_state + 4 * i);
    }
}