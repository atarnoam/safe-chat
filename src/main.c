#include <stdio.h>

#include "gf_operations.h"
#include "key_schedule.h"

void print_byte_arr(const byte *a, size_t n) {
    for (size_t i = 0; i < n; ++i) {
        printf("%x ", a[i]);
    }
    printf("\n");
}

int main() {

    for (int i = 0; i < 256; ++i) {
        byte s = s_box(i);
        printf("0x%02x ", s);
        if ((i + 1) % 16 == 0)
            printf("\n");
    }
    printf("\n");

    return 0;
}