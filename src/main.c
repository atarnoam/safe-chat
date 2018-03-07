#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>

#include "gf_operations.h"
#include "key_schedule.h"
#include "cbc.h"
#include "base64.h"

extern inline void print_word(word a, bool newl);

/* The program takes 5 arguments:
 * 1. The mode of operation (encoding / decoding).
 * 2. The name of the input file.
 * 3. The name of the output file.
 * 4. The key.
 * 5. The initialization vector (iv).
 */

int main(int argc, char* argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s [-ed] input output key iv", argv[0]);
        return 1;
    }
    char mode = 0;
    int c;

    while ((c = getopt(argc, argv, "ed")) != -1)
        switch (c)
        {
            case 'e':
                mode = 'e';
                break;
            case 'd':
                mode = 'd';
                break;
            default:
                fprintf(stderr, "Usage: %s [-ed] input output key iv\n", argv[0]);
        }

    if (strlen(argv[4]) != 44) {
        fprintf(stderr, "Size of key must be 32 chars (the base64 must be 44 chars).\n");
        return 1;
    }
    byte* key = malloc(33);
    if (!key) {
        fprintf(stderr, "Out of memory.\n");
        return 1;
    }
    Base64decode((char *)key, argv[4]);

    word *expanded_key = malloc(60 * sizeof(word));
    if (!expanded_key) {
        fprintf(stderr, "Out of memory.\n");
        return 1;
    }

    key_schedule(key, expanded_key);

    if (strlen(argv[5]) != 24) {
        fprintf(stderr, "Size of key must be 16 chars (the base64 must be 24 chars).\n");
        return 1;
    }
    word* iv = malloc(17);
    if (!iv) {
        fprintf(stderr, "Out of memory.\n");
        return 1;
    }
    Base64decode((char*)iv, argv[5]);

    if (mode == 'e')
        encrypt_file(argv[1], argv[2], expanded_key, iv);
    else
        decrypt_file(argv[1], argv[2], expanded_key, iv);

    return 0;
}