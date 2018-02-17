//
// Created by Noam on 25/12/2017.
//

#include <stdio.h>
#include "gf_operations.h"
/*
 * In this file, we are dealing with bytes, which we see as polynomials over the finite field consisting of all
 * polynomials with coefficients in Z2 = {0, 1} with degree less than 8, with operations of addition and multiplication
 * modulus p, where p(x) = x^8+x^4+x^3+x+1.
 */

//Notice that the x^8 coefficient of p isn't there. That is because p is only the size of one byte.
const byte p = 0b00011011; // = 0x1B

byte mul(byte a, byte b) {
    byte t = 0;
    short temp_shift; // short is two bytes
    while (a && b) {
        if (b & 1) {
            t = ADD(t, a);
        }
        temp_shift = a << 1; // temp_shift = a*x
        a = (byte) temp_shift; // a = a * x
        if (temp_shift & 0x100) { // maybe we need to add p to t.
            a = ADD(a, p);
        }
        b >>= 1;  // b = b / x
    }
    return t;
}

int deg(short a) {
    if (a == 0) {
        return -1;
    }
    int d = 0;
    while (a >>= 1) {
        ++d;
    }
    return d;
}

// divides two polynomials over Z2[x].
// The quotient is in res[0] and the remainder in res[1].
void div(short f, byte g, byte *res) {
    short h = f;
    byte q = 0, monom;
    while (deg(h) >= deg(g)) {
        monom = (byte) 1 << (deg(h) - deg(g));
        q = ADD(q, monom);
        h = ADD(h, (byte) (g << (deg(h) - deg(g))));
    }
    res[0] = q;
    res[1] = (byte) h;
}

// a good old swap function
static void swap(byte *a, byte *b) {
    byte temp = *a;
    *a = *b;
    *b = temp;
}

// a^-1 (mod p). We assume that a != 0.
byte inverse(byte a) {
    byte t = 0, new_t = 1, div_res[2], new_r = a;
    short r = 0x11B;
    while (new_r) {
        div(r, new_r, div_res);
        r = div_res[1];
        swap(&new_r, (byte *) &r);
        t = ADD(t, mul(div_res[0], new_t));
        swap(&new_t, &t);
    }
    return t;
}

static inline byte rotate_left(byte a) {
    return (a << 1) | (a >> 7);
}

// the Rijndael substitution box
byte s_box(byte a) {
    byte s = inverse(a), result = 0;
    for (int i = 0; i < 5; ++i) {
        result = ADD(result, s);
        s = rotate_left(s);
    }
    return (byte) (result ^ 0x63);
}

static inline byte rotate_right(byte a) {
    return (a >> 1) | (a << 7);
}

// returns parity of number of 1 bits in x
static inline int parity(byte x) {
    x ^= x >> 4;
    x ^= x >> 2;
    x ^= x >> 1;
    return x & 1;
}

// the inverse Rijndael substitution box
byte inv_s_box(byte a) {
    byte row = 0b01010010, result = 0;

    // we are caculating a matrix multiplication.
    for (int i = 0; i < 8; ++i) {
        result <<= 1;
        if (parity(row & a)) {
            result |= 1;
        }
        row = rotate_right(row);
    }

    // add a vector
    result ^= 0x05;

    // return the inverse
    return inverse(result);
}