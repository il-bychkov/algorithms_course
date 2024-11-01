#include <stdio.h>
#include <stdint.h>

void print_bits_hi_to_lo(uint8_t value) {
    printf("0b");


    for (int j = 8 - 1; j >= 0; j--) {
        printf("%d", (value >> j) & 0x1);
    }

    printf("\n");
}

// - пример битовых операторов (AND, OR, XOR, NOT)

int main()
{
    uint8_t a = 9; // 0b1001
    uint8_t b = 0b111;

    printf("Bitwise AND result = ");
    print_bits_hi_to_lo(a & b);
    printf("Bitwise OR  result = ");
    print_bits_hi_to_lo(a | b);
    printf("Bitwise XOR result = ");
    print_bits_hi_to_lo(a ^ b);
    printf("Bitwise NOT result = ");
    print_bits_hi_to_lo(~ a);

    return 0;
}
