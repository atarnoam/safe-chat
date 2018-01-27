//
// Created by Noam on 25/12/2017.
//

#ifndef AES_GF_OPERATIONS_H
#define AES_GF_OPERATIONS_H

typedef unsigned char byte;

const byte p;

// sum of two polynomials mod p
#define ADD(x, y) (byte)((x) ^ (y))

// product of two polynomials mod p
byte mul(byte a, byte b);

byte s_box(byte a);

byte inv_s_box(byte a);

#endif //AES_GF_OPERATIONS_H
