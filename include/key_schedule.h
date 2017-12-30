//
// Created by Noam on 26/12/2017.
//

#ifndef AES_KEY_SCHEDULE_H
#define AES_KEY_SCHEDULE_H

#include "gf_operations.h"

#define N 32

typedef unsigned int word; // a word is an array of 4 bytes.

// 2^(n-1) mod p, n > 0
byte rcon(int n);

void key_schedule(const byte key[], word expanded_key[]);

byte byte_at(word a, int i);

#endif //AES_KEY_SCHEDULE_H
