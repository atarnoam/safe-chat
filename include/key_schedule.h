//
// Created by Noam on 26/12/2017.
//

#ifndef AES_KEY_SCHEDULE_H
#define AES_KEY_SCHEDULE_H

#include "gf_operations.h"

typedef unsigned int word; // a word is an array of 4 bytes.

void key_schedule(const byte key[], word expanded_key[]);

byte byte_at(word a, int i);

word sub_word(word w);

#endif //AES_KEY_SCHEDULE_H
