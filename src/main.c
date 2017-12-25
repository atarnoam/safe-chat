#include <stdio.h>

#include "gf_operations.h"

int main() {
    byte x = 0x1, y = 0x2;
    printf("%d", mul(x, y));
    return 0;
}