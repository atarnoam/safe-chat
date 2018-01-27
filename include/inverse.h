//
// Created by Rami on 26/01/2018.
//

#ifndef AES_INVERSE_H
#define AES_INVERSE_H

#include "cypher.h"

void decrypt(word ciphertext[4], const word expanded_key[]);

/*
void inv_mix_columns(word state[4]);

void inv_sub_bytes(word s[4]);

void inv_shift_rows(word s[4]);
*/

#endif //AES_INVERSE_H

