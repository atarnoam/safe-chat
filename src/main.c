#include <stdio.h>

#include "gf_operations.h"

int main() {
    byte x = 0x80;
    byte y = 0b10;
    printf("%d\n", deg(x));
    printf("%x\n", mul(x, y));
    return 0;
}