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
    return w << 8 * i | w >> 8 * (4 - i);
}

// the shift_rows stage
void shift_rows(word s[4]) {
    for (int i = 1; i < 4; ++i) {
        s[i] = rotate_left(s[i], i);
    }
}

//take 4 words and turn them into a 4x4 byte matrix
void to_matrix(word s[4], byte mat[4][4]) {
    for (int i = 0; i < 4; ++i) {
        byte *as_word = ((byte *) &s[i]);
        for (int j = 0; j < 4; j++) {
            mat[i][j] = as_word[3 - j];
        }
    }
}
