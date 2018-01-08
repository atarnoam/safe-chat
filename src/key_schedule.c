//
// Created by Noam on 26/12/2017.
//

#include "key_schedule.h"

// Notice this is AES-256 thus the key size is 32 bytes.
// N - the key size
// B - the expanded key size.

// Turn 4 bytes to int
static inline word create_word(const byte a[4]) {
    return *((word *) a);
}

byte rcon(int n) {
    byte exp = 0x01, two = 0x02;
    for (int i = 1; i < n; ++i) {
        exp = mul(exp, two);
    }
    return exp;
}

// provided a word, it rotates it 1 byte to the left. Yes, I am rotating it to the right. Blame Intel.
static inline word rotate(word w) {
    return w >> 8 | w << 8 * 3;
}

// Applies s_box to all four bytes in the word
word sub_word(word w) {
    byte *p = ((byte *) (&w));
    for (int i = 0; i < 4; ++i) {
        p[i] = s_box(p[i]);
    }
    return create_word(p);
}

// The core of the algorithm
static inline word key_schedule_core(word w, int iter) {
    w = sub_word(rotate(w));
    w ^= rcon(iter);
    return w;
}

void key_schedule(const byte key[], word expanded_key[]) {
    word temp;
    int i = 0;
    for (; i < 8; ++i) {
        word curr = create_word(key + 4 * i);
        expanded_key[i] = curr;
    }

    for (; i < 60; ++i) {
        temp = expanded_key[i - 1];
        if (i % 8 == 0) {
            temp = key_schedule_core(temp, i / 8);
        } else if (i % 8 == 4) {
            temp = sub_word(temp);
        }
        expanded_key[i] = expanded_key[i - 8] ^ temp;
    }
}