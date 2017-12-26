//
// Created by Noam on 26/12/2017.
//

#include "key_schedule.h"

byte rcon(int n) {
    byte exp = 0x01, two = 0x02;
    for (int i = 1; i < n; ++i) {
        exp = mul(exp, two);
    }
    return exp;
}
