//
// Created by Noam on 25/12/2017.
//

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
        b >>= 1;  // b = b / x
        temp_shift = a << 1;
        if (temp_shift & 0x100) { // maybe we need to add p to t.
            t = ADD(t, p);
        }
        a = (byte) temp_shift; // a = a*x
    }
    return t;
}

int deg(byte a) {
    if (a == 0) {
        return -1;
    }
    int d = 0;
    while (a >>= 1) {
        ++d;
    }
    return d;
}