//
// Created by Noam on 31/12/2017.
//

#ifndef AES_CYPHER_H
#define AES_CYPHER_H

#include "key_schedule.h"

void add_round_key(word state[4], const word key[4]);

void encrypt(word plaintext[4], const word expanded_key[4]);

void transpose(word state[4]);

/*
void shift_rows(word s[4]);

void mix_columns(word state[4]);

void sub_bytes(word s[4]);
*/
#endif //AES_CYPHER_H
