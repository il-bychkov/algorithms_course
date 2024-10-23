#include <stdio.h>
#include <stdint.h>

void print_bits_hi_to_lo(uint8_t value) {
    printf("0b");


    for (int j = 8 - 1; j >= 0; j--) {
        printf("%d", (value >> j) & 0x1);
    }

    printf("\n");
}

int main() {

    uint8_t two = 2;
    int8_t plus_two = 2;
    int8_t minus_two = -2;

    printf("unsigned %d = ", two);
    print_bits_hi_to_lo(two);

    printf("signed %d   = ", plus_two);
    print_bits_hi_to_lo(plus_two);

    printf("signed %d   = ", minus_two);
    print_bits_hi_to_lo(minus_two);

    return 0;
}
