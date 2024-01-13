#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


void lfsr_fib_8bit(char *output, size_t length) {
    uint8_t start_state = 0b01010101;  /* Any nonzero start state will work. */
    uint8_t lfsr = start_state;
    uint8_t bit;

    for (size_t i = 0; i < length; ++i) {
        uint8_t output_number = 0;
        for (size_t j = 0; j < 8; ++j) {
            // generate new bit by XOR'ing setwise co-prime bits
            bit = ((lfsr >> 0) ^ (lfsr >> 2) ^ (lfsr >> 3) ^ (lfsr >> 5)) & 1u;
            // move rightest bit to generated number
            output_number = (output_number << 1) | (lfsr & 1u);
            // release one rightest bit and allocate leftest bit for new boolean value by shift
            // 1110 -> 0111
            lfsr = lfsr >> 1;
            // place new boolean value to leftest bit
            // bit = 101[1]; bit << 4 = [1]000; 0111 + [1]000 = 1111
            lfsr = lfsr | (bit << 7);
        }
        output[i] = output_number;
    }
}

void otp(char *input, char *key, size_t length) {
    for (int i = 0; i < length; ++i){
        input[i] = input[i] ^ key[i];
    }
};

int main() {
    char text[256];
    unsigned char key[256];

    printf("Input text:\n");
    scanf("%s", text);
    size_t input_length = strlen(text);

    lfsr_fib_8bit(key, input_length);
    printf("Generated key:\n");
    for (int i = 0; i < input_length; ++i) {
        printf("%u ", key[i]);
    }
    printf("\n");

    otp(text, key, input_length);
    printf("Encrypted text:\n%s\n", text);

    otp(text, key, input_length);
    printf("Decrypted text:\n%s\n", text);
}