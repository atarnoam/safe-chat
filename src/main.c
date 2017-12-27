#include <stdio.h>

#include "gf_operations.h"
#include "key_schedule.h"

int main() {
    byte x[10] = {0x2};
    printf("%x\n", mul(0x40, 0x02));
    for (int i = 1; i < 10; ++i) {
        x[i] = mul(x[i - 1], 0x02);
        printf("%x ", x[i]);
    }
    printf("\n");
    printf("%x, %x, %x, %x\n", rcon(4), rcon(6), rcon(8), rcon(255));
    return 0;
}