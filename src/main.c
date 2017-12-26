#include <stdio.h>

#include "gf_operations.h"
#include "key_schedule.h"

int main() {
    byte x = 0x80;
    byte y = 0b10;
    printf("%d\n", deg(x));
    printf("%x\n", mul(x, y));
    printf("%x, %x, %x, %x\n", rcon(4), rcon(6), rcon(8), rcon(255));
    return 0;
}