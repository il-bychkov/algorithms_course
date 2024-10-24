#include <stdio.h>
#include <stdint.h>

// - пример двоичных масок (выделение байт)
// - примеры двоичных сдвигов (лево, право)

uint8_t get_byte(int value) {
    return value & 0xFF;
}

void print_bytes_hi_to_lo(int value) {

    printf("0x");

    for (int i = sizeof(int) - 1; i >= 0; i--) {
        // printf("%d\n", i);
        printf("%02x", get_byte(value >> i * 8));
    }

    printf("\n");
}

void print_bits_hi_to_lo(int value) {
    printf("0b");

    for (int i = sizeof(int) - 1; i >= 0; i--) {
        uint8_t byte = get_byte(value >> i * 8);

        for (int j = 8 - 1; j >= 0; j--) {
            printf("%d", (byte >> j) & 0x1);
        }
    }

    printf("\n");
}

int main() {
    int value = 12;

    printf("0x%08x\n", value);

    print_bytes_hi_to_lo(value);
    print_bits_hi_to_lo(value);

    return 0;
}
