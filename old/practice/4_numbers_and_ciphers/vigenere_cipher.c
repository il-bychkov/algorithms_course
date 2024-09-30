#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define ASCII_START 65
#define ASCII_END 90

const uint16_t alphabet_len = ASCII_END - ASCII_START + 1;

uint8_t get_number_by_char(char c) {
    uint8_t num = (uint8_t)c;
    if (num < ASCII_START || num > ASCII_END) {
        printf("'%c' not in alphabet\n");
        exit(1);
    }
    return num - ASCII_START;
}

char get_char_by_number(uint8_t num) {
    num += ASCII_START;
    if (num < ASCII_START || num > ASCII_END) {
        printf("'%c' not in alphabet\n");
        exit(1);
    }
    return (char)num;
}

void vigenere_encrypt(char *input, size_t length, char *key, size_t key_length) {
    for (size_t index = 0; index < length; ++index) {
        size_t key_index = index % key_length;

        uint16_t key_num = get_number_by_char(key[key_index]);
        uint16_t input_num = get_number_by_char(input[index]);

        uint16_t encrypted_index = (input_num + key_num) % alphabet_len;
        input[index] = get_char_by_number(encrypted_index);
    }
};

void vigenere_decrypt(char *input, size_t length, char *key, size_t key_length) {
    for (size_t index = 0; index < length; ++index) {
        size_t key_index = index % key_length;

        uint16_t key_num = get_number_by_char(key[key_index]);
        uint16_t input_num = get_number_by_char(input[index]);

        int32_t decrypted_index = ((int32_t)input_num - (int32_t)key_num) % (int32_t)alphabet_len;
        if (decrypted_index < 0) {
            decrypted_index += alphabet_len;
        }

        input[index] = get_char_by_number(decrypted_index);
    }
};


int main() {
    char text[256];
    char key[256];
    printf("Input text:\n");
    scanf("%s", text);
    size_t input_length = strlen(text);
    printf("Key:\n");
    scanf("%s", key);
    size_t key_length = strlen(key);

    vigenere_encrypt(text, input_length, key, key_length);
    printf("Encrypted text:\n%s\n", text);

    vigenere_decrypt(text, input_length, key, key_length);
    printf("Decrypted text:\n%s\n", text);

    // ex.
    // input: ATTACKATDAWN
    // key:   LEMON
}