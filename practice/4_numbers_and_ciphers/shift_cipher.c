#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

const size_t alphabet_len = 26;
const char alphabet[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                         'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's',
                         't', 'u', 'v', 'w', 'x', 'y', 'z'};

size_t find_character_index(char c) {
    for (int i = 0; i < alphabet_len; ++i) {
        if (c == alphabet[i]) {
            return i;
        }
    }
    return -1;
}

void shift_encrypt(char *input, size_t length, size_t shift) {
    for (size_t index = 0; index < length; ++index) {
        size_t index_in_alphabet = find_character_index(input[index]);
        if (index_in_alphabet < 0) {
            printf("No character '%c' in alphabet\n", input[index]);
            exit(1);
        }

        size_t encrypted_index = (index_in_alphabet + shift) % alphabet_len;
        input[index] = alphabet[encrypted_index];
    }
};

void shift_decrypt(char *input, size_t length, size_t shift) {

    for (size_t index = 0; index < length; ++index) {
        long long int index_in_alphabet = find_character_index(input[index]);
        if (index_in_alphabet < 0) {
            exit(1);
        }

        int decrypted_index = (index_in_alphabet - (long long int)shift) % (long long int)alphabet_len;
        if (decrypted_index < 0) {
            decrypted_index += alphabet_len;
        }

        input[index] = alphabet[decrypted_index];
    }
};


int main() {
    char text[256];
    size_t shift;
    printf("Input text:\n");
    scanf("%s", text);
    size_t input_length = strlen(text);
    printf("Shift:\n");
    scanf("%zu", &shift);

    shift_encrypt(text, input_length, shift);
    printf("Encrypted text:\n%s\n", text);

    shift_decrypt(text, input_length, shift);
    printf("Decrypted text:\n%s\n", text);
}