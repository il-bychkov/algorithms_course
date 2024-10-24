#include <stdio.h>
#include <stdint.h>

void print_bits_hi_to_lo(uint8_t value) {
    printf("0b");


    for (int j = 8 - 1; j >= 0; j--) {
        printf("%d", (value >> j) & 0x1);
    }

    printf("\n");
}

uint8_t set_bit(uint8_t value, size_t bit) {
    return value |= 1 << bit;
}

uint8_t clear_bit(uint8_t value, size_t bit) {
    return value &= ~(1 << bit);
}

uint8_t flip_bit(uint8_t value, size_t bit) {
    return value ^= 1 << bit;
}

uint8_t check_bit(uint8_t value, size_t bit) {
    return (value & (1 << bit)) >> bit;
}


int main() {
    uint8_t value = 0b00100100;

    size_t bit2 = 2;
    size_t bit3 = 3;
    size_t bit5 = 5;

    printf("initial value           = ");
    print_bits_hi_to_lo(value);

    value = set_bit(value, bit3);
    printf("value after set bit %d  = ", bit3);
    print_bits_hi_to_lo(value);

    value = clear_bit(value, bit2);
    printf("value after set bit %d  = ", bit2);
    print_bits_hi_to_lo(value);

    value = flip_bit(value, bit2);
    printf("value after flip bit %d = ", bit2);
    print_bits_hi_to_lo(value);

    value = flip_bit(value, bit3);
    printf("value after flip bit %d = ", bit3);
    print_bits_hi_to_lo(value);

    printf("is bit %d set           = %d\n", bit5, check_bit(value, bit5));

    return 0;
}

