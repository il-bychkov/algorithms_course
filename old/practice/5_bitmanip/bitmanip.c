#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


uint64_t apply_mask(uint64_t value, uint64_t mask) {
    return value & mask;
}

uint64_t shift_right(uint64_t value, size_t shift_amount) {
    return value >> shift_amount;
}

uint64_t shift_left(uint64_t value, size_t shift_amount) {
    return value << shift_amount;
}

uint8_t get_byte(uint64_t value, size_t n_byte) {

    uint64_t mask = 0xFF;
    size_t shift_amount = n_byte * 8;

    value = shift_right(value, shift_amount);
    value = apply_mask(value, mask);

    return value;
}

bool check_bit(uint8_t value, size_t n_bit) {
    return (value >> n_bit) & 0x1;
}

void hexdump(uint64_t value) {
    printf("%x, ", get_byte(value, 0));
    printf("%x, ", get_byte(value, 1));
    printf("%x, ", get_byte(value, 2));
    printf("%x, ", get_byte(value, 3));
    printf("%x, ", get_byte(value, 4));
    printf("%x, ", get_byte(value, 5));
    printf("%x, ", get_byte(value, 6));
    printf("%x\n", get_byte(value, 7));
}

int main() {

    uint64_t value = 0xAAD45A121D34F13C;

    hexdump(value);


    // check value of 13'th bit
    // uint64_t bytes layout - 0-7, 8-15, 16-31, ...
    // so take 1'st byte

    uint8_t byte = get_byte(value, 1);

    // 13 - 8 = 5
    // fifth bit

    bool isBitSet = check_bit(byte, 5);

    if(isBitSet) {
        printf("Bit is 1\n");
    } else {
        printf("Bit is 0\n");
    }

    return 0;
}
