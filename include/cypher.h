//
// Created by Noam on 31/12/2017.
//

#ifndef AES_CYPHER_H
#define AES_CYPHER_H

#include "key_schedule.h"

void shift_rows(word s[4]);

void to_matrix(word s[4], byte mat[4][4]);

#endif //AES_CYPHER_H
