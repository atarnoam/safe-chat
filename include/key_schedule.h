//
// Created by Noam on 26/12/2017.
//

#ifndef AES_KEY_SCHEDULE_H
#define AES_KEY_SCHEDULE_H

#include <stdint.h>
#include "gf_operations.h"

/* A word is an array of 4 bytes.
 * Because we are working on a Intel CPU, which uses little endian format, The bytes in the word
 * will be stored accordingly.
 */
typedef uint32_t word;

void key_schedule(const byte key[], word expanded_key[]);

word sub_word(word w);

#endif //AES_KEY_SCHEDULE_H
