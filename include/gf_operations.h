//
// Created by Noam on 25/12/2017.
//

#ifndef AES_GF_OPERATIONS_H
#define AES_GF_OPERATIONS_H

typedef unsigned char byte;

const byte p;

inline byte add(byte a, byte b) {
    return a ^ b;
}

#endif //AES_GF_OPERATIONS_H
