//
// Created by Noam on 26/12/2017.
//

#include "key_schedule.h"

// Notice this is AES-256 thus the key size is 32 bytes.
// N - the key size
// B - the expanded key size.

// Turn 4 bytes to int
static inline word create_word(const byte a[4]) {
    return (a[0] << 8 * 3) | (a[1] << 8 * 2) | (a[2] << 8) | a[3];
}


byte rcon(int n) {
    byte exp = 0x01, two = 0x02;
    for (int i = 1; i < n; ++i) {
        exp = mul(exp, two);
    }
    return exp;
}

inline byte byte_at(word a, int i) {
    return (byte) (a >> 8 * (7 - i));
}

// provided a word, it rotates it 1 byte to the left
static inline word rotate(word w) {
    return w << 8 | w >> 8 * 3;
}

// Applies s_box to all four bytes in the word
word sub_word(word w) {
    word s_w = 0;
    for (int i = 0; i < 4; ++i) {
        s_w <<= 8;
        s_w |= s_box(byte_at(w, i));
    }
    return s_w;
}

// The core of the algorithm
static inline word key_schedule_core(word w, int iter) {
    w = sub_word(rotate(w));
    w ^= rcon(iter) << 8 * 3;
    return w;
}

void key_schedule(const byte key[], word expanded_key[]) {
    word temp;
    int i = 0;
    while (i < 8) {
        expanded_key[i] = create_word(key + 4 * i);
        i++;
    }

    while (i < 60) {
        temp = expanded_key[i - 1];
        if (i % 8 == 0) {
            temp = key_schedule_core(temp, i / 8);
        } else if (i % 8 == 4) {
            temp = sub_word(temp);
        }
        expanded_key[i] = expanded_key[i - 8] ^ temp;
        i++;
    }
}