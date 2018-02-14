//
// Created by Rami on 14/02/2018.
//

#ifndef AES_CBC_H
#define AES_CBC_H

#include "cypher.h"
#include "inverse.h"

#include "stddef.h"

void cbc_encrypt(word *plaintext, const word *expanded_key, const word *iv, size_t pt_length);

#endif //AES_CBC_H
