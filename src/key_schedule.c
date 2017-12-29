//
// Created by Noam on 26/12/2017.
//

#include "key_schedule.h"

byte rcon(int n) {
    byte exp = 0x01, two = 0x02;
    for (int i = 1; i < n; ++i) {
        exp = mul(exp, two);
    }
    return exp;
}

// provided a 32-bit word, it rotates it 1 byte to the left
void rotate(byte a[4]) {
    byte temp = a[0];

    for (int i = 0; i < 2; ++i) {
        a[i] = a[i + 1];
    }
    a[3] = temp;
}