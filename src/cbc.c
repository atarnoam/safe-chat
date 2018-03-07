//
// Created by Noam on 14/02/2018.
//

#include <stdio.h>
#include <malloc.h>
#include <mem.h>
#include "cbc.h"

// number of bytes read in each section
#define BLOCK_SIZE 256
// size of block encrypted in aes (128 bits)
#define AES_BLOCK_SIZE (4*sizeof(word))

// a, b are 16 bytes long. does a = a ^ b.
void xor_mem(word *a, const word *b) {
    for (int i = 0; i < 4; ++i) {
        *a ^= *b;
        a++, b++;
    }
}

//pt_length is in bytes
//We suppose pt_length % 16 == 0
void cbc_encrypt(word *plaintext, const word *expanded_key, const word *iv, size_t pt_length) {
    size_t num_of_rounds = pt_length / 16;
    const word *prev = iv;
    for (size_t i = 0; i < num_of_rounds; ++i) {
        xor_mem(plaintext, prev);
        encrypt(plaintext, expanded_key);
        prev = plaintext;
        plaintext += 4;
    }
}


int encrypt_file(const char* input_name, const char* output_name, const word *expanded_key, const word* iv) {
    FILE *input, *output;
    if (!(input = fopen(input_name, "rb"))) {
        return -1;
    }
    if (!(output = fopen(output_name, "wb"))) {
        fclose(input);
        return -1;
    }

    word* buffer = malloc(BLOCK_SIZE);
    if (!buffer) {
        fclose(input);
        fclose(output);
        return -1;
    }

    word* prev = malloc(AES_BLOCK_SIZE);
    if (!prev) {
        free(buffer);
        fclose(input);
        fclose(output);
    }
    memcpy(prev, iv, AES_BLOCK_SIZE);

    size_t read;
    while ((read = fread(buffer, sizeof(byte), BLOCK_SIZE, input)) == BLOCK_SIZE) {
        cbc_encrypt(buffer, expanded_key, prev, BLOCK_SIZE);
        memcpy(prev, buffer + (BLOCK_SIZE - AES_BLOCK_SIZE) / sizeof(word), AES_BLOCK_SIZE);
        fwrite(buffer, sizeof(byte), BLOCK_SIZE, output);
    }
    memset((byte *)buffer + read, AES_BLOCK_SIZE - (read % AES_BLOCK_SIZE), AES_BLOCK_SIZE - (read % AES_BLOCK_SIZE));
    read += AES_BLOCK_SIZE - read % AES_BLOCK_SIZE;
    cbc_encrypt(buffer, expanded_key, prev, read);
    fwrite(buffer, sizeof(byte), read, output);

    //Closing sequence
    free(prev);
    free(buffer);
    fclose(input);
    fclose(output);
    return 1;
}

void cbc_decrypt(word *ciphertext, const word *expanded_key, const word *iv, size_t pt_length) {
    size_t num_of_rounds = pt_length / 16;
    word *prev = malloc(AES_BLOCK_SIZE), *temp = malloc(AES_BLOCK_SIZE);
    memcpy(prev, iv, 4*sizeof(word));
    for (size_t i = 0; i < num_of_rounds; ++i) {
        memcpy(temp, ciphertext, AES_BLOCK_SIZE);
        decrypt(ciphertext, expanded_key);
        xor_mem(ciphertext, prev);
        memcpy(prev, temp, AES_BLOCK_SIZE);
        ciphertext += 4;
    }
    free(prev);
    free(temp);
}

static inline long size_of_file(FILE *f) {
    fseek(f, 0L, SEEK_END);
    long sz = ftell(f);
    rewind(f);
    return sz;
}

int decrypt_file(const char* input_name, const char* output_name, const word *expanded_key, const word* iv) {
    FILE *input, *output;
    if (!(input = fopen(input_name, "rb"))) {
        return -1;
    }
    if (!(output = fopen(output_name, "wb"))) {
        fclose(input);
        return -1;
    }

    word* buffer = malloc(BLOCK_SIZE);
    if (!buffer) {
        fclose(input);
        fclose(output);
        return -1;
    }

    long sz = size_of_file(input);
    long num_of_steps = (sz / BLOCK_SIZE) - ((sz % BLOCK_SIZE)? 0 : 1);

    word* prev = malloc(AES_BLOCK_SIZE), *temp = malloc(AES_BLOCK_SIZE);
    memcpy(prev, iv, AES_BLOCK_SIZE);

    size_t read = fread(buffer, sizeof(byte), BLOCK_SIZE, input);
    for(long i = 0; i < num_of_steps; i++) {
        memcpy(temp, buffer + (BLOCK_SIZE - AES_BLOCK_SIZE) / sizeof(word), AES_BLOCK_SIZE);
        cbc_decrypt(buffer, expanded_key, prev, BLOCK_SIZE);
        memcpy(prev, temp, AES_BLOCK_SIZE);
        fwrite(buffer, sizeof(byte), BLOCK_SIZE, output);
        read = fread(buffer, sizeof(byte), BLOCK_SIZE, input);
    }
    if (read) {
        cbc_decrypt(buffer, expanded_key, prev, read);
        byte padded = ((byte*)buffer)[read-1];
        read -= padded? padded: 16;
        fwrite(buffer, sizeof(byte), read, output);
    }

    // Closing sequence
    free(temp);
    free(prev);
    free(buffer);
    fclose(input);
    fclose(output);
    return 1;
}
