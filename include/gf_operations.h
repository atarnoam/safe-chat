//
// Created by Noam on 25/12/2017.
//

#ifndef AES_GF_OPERATIONS_H
#define AES_GF_OPERATIONS_H

#include "bytes.h"

typedef byte polynomial;

const polynomial p;

inline polynomial add(polynomial a, polynomial b) {
    return xor(a, b);
}

#endif //AES_GF_OPERATIONS_H
