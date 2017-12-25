//
// Created by Rami on 25/12/2017.
//

#ifndef AES_BYTES_H
#define AES_BYTES_H

typedef unsigned char byte;

extern inline byte and(byte x, byte y);

extern inline byte or(byte x, byte y);

extern inline byte lshift(byte x, int n);

extern inline byte rshift(byte x, int n);

#endif //AES_BYTES_H
