//
// Created by Rami on 25/12/2017.
//

#include "../include/bytes.h"

inline byte and(byte x, byte y) {
    return (byte) (x & y);
}

inline byte or(byte x, byte y) {
    return (byte) (x | y);
}

inline byte lshift(byte x, int n) {
    return (byte) (x << n);
}

inline byte rshift(byte x, int n) {
    return (byte) (x >> n);
}

//inline byte and(byte x, )