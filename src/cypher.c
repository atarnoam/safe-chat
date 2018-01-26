//
// Created by Noam on 31/12/2017.
//

#include "cypher.h"
#include "print_debug.h"


#define DEBUG 0

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

// the shift_rows stage, this is actually a shift columns
void shift_rows(word s[4]) {
    // this is actually a 4x4 matrix, note that "mat[i][j]" is mat[4*i + j].
    byte *mat = (byte *) s;

    for (int j = 1; j < 4; ++j) {
        //rotate jth row j times to the left
        for (int k = 0; k < j; ++k) {
            byte temp = mat[j];
            for (int i = 0; i < 3; ++i) {
                mat[4 * i + j] = mat[4 * (i + 1) + j];
            }
            mat[4 * 3 + j] = temp;
        }
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

void mix_column(byte *r) {
    byte a[4];
    byte b[4];
    byte c;
    byte h;
    for (c = 0; c < 4; c++) {
        a[c] = r[c];
        h = r[c] & (byte) 0x80; /* hi bit */
        b[c] = r[c] << 1; // b[c] = gmul(r[c],2);
        if (h == 0x80)
            b[c] ^= 0x1b;
    }
    r[0] = b[0] ^ a[3] ^ a[2] ^ b[1] ^ a[1];
    r[1] = b[1] ^ a[0] ^ a[3] ^ b[2] ^ a[2];
    r[2] = b[2] ^ a[1] ^ a[0] ^ b[3] ^ a[3];
    r[3] = b[3] ^ a[2] ^ a[1] ^ b[0] ^ a[0];
}

void mix_columns(word state[4]) {
    for (int i = 0; i < 4; ++i) {
        mix_column((byte *) (state + i));
    }
}

void transpose(word state[4]) {
    byte *mat = (byte *) state;
    byte temp;
    for (int i = 1; i < 4; ++i) {
        for (int j = 0; j < i; ++j) {
            temp = mat[4 * i + j];
            mat[4 * i + j] = mat[i + 4 * j];
            mat[i + 4 * j] = temp;
        }
    }
}

// encrypts plaintext, uses expanded key.
void encrypt(word plaintext[4], word expanded_key[]) {
    debug_print("encrypting message...\n\n");

    debug_print("Round 0:\n");

    add_round_key(plaintext, expanded_key);
    expanded_key += 4;

    if (DEBUG) {
        print_state(plaintext);
        printf("\n");
    }

    for (int i = 1; i < 14; ++i, expanded_key += 4) {
        debug_print("Round %d:\n", i);

        sub_bytes(plaintext);

        debug_print("After sub_bytes:\n");
        if (DEBUG) {
            print_state(plaintext);
            printf("\n");
        }

        shift_rows(plaintext);

        debug_print("After shift_rows:\n");
        if (DEBUG) {
            print_state(plaintext);
            printf("\n");
        }

        mix_columns(plaintext);

        debug_print("After mix_columns:\n");
        if (DEBUG) {
            print_state(plaintext);
            printf("\n");
        }

        add_round_key(plaintext, expanded_key);

        debug_print("End of round:\n");
        if (DEBUG) {
            print_state(plaintext);
            printf("\n");
        }
    }

    debug_print("Round 14:\n");
    sub_bytes(plaintext);
    shift_rows(plaintext);
    add_round_key(plaintext, expanded_key);

    if (DEBUG) {
        print_state(plaintext);
        printf("\n");
    }

}