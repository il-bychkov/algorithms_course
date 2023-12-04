#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const size_t alphabet_len = 4;
const char main_alphabet[] = {'a', 'b', 'c', 'd'};
const char subs_alphabet[] = {'.', ',', '-', '_'};

size_t find_character_index(char c, const char alphabet[]) {
    for (int i = 0; i < alphabet_len; ++i) {
        if (c == alphabet[i]) {
            return i;
        }
    }
    return -1;
}

void subs_encrypt(char *input, size_t length) {
    for (size_t index = 0; index < length; ++index) {
        size_t index_in_alphabet = find_character_index(input[index], main_alphabet);
        if (index_in_alphabet < 0) {
            printf("No character '%c' in alphabet\n", input[index]);
            exit(1);
        }

        input[index] = subs_alphabet[index_in_alphabet];
    }
};

void subs_decrypt(char *input, size_t length) {

    for (size_t index = 0; index < length; ++index) {
        size_t index_in_alphabet = find_character_index(input[index], subs_alphabet);
        if (index_in_alphabet < 0) {
            exit(1);
        }

        input[index] = main_alphabet[index_in_alphabet];
    }
};


int main() {
    char text[256];
    size_t shift;
    printf("Input text:\n");
    scanf("%s", text);
    size_t input_length = strlen(text);

    subs_encrypt(text, input_length);
    printf("Encrypted text:\n%s\n", text);

    subs_decrypt(text, input_length);
    printf("Decrypted text:\n%s\n", text);
}