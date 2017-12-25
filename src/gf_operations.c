//
// Created by Noam on 25/12/2017.
//

#include "gf_operations.h"

/*
 * In this file, we are dealing with bytes, which we see as polynomials ober the finite field consisting of all
 * polynomials with coefficients in Z2={0, 1} with degree less than 8, with operations of addition and multiplication
 * modulus p, where p(x) = x^8+x^4+x^3+x+1. Notice that the x^8 coefficient of p isn't there. That is because p is
 * only the size of one byte.
 */

const byte p = 0b00011011; // = 0x1B
