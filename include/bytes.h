//
// Created by Noam on 25/12/2017.
//

#ifndef AES_BYTES_H
#define AES_BYTES_H

typedef unsigned char byte;

inline byte and(byte x, byte y) {
    return (byte) (x & y);
}

inline byte or(byte x, byte y) {
    return (byte) (x | y);
}

inline byte xor(byte x, byte y) {
    return (byte) (x ^ y);
}

inline byte lshift(byte x, int n) {
    return (byte) (x << n);
}

inline byte rshift(byte x, int n) {
    return (byte) (x >> n);
}

#endif //AES_BYTES_H
