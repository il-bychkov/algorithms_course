#include <stdio.h>
#include <stdint.h>

// need explicit size types here
uint8_t get_byte(int value) {
    return value & 0xFF;
}

int main() {
    int value = 0xA1B2C3D4;

    printf("full value = 0x%x\n", value);
    printf("byte 0     = 0x%x\n", get_byte(value));
    printf("byte 1     = 0x%x\n", get_byte(value >> 8));
    printf("byte 2     = 0x%x\n", get_byte(value >> 8 * 2));
    printf("byte 3     = 0x%x\n", get_byte(value >> 8 * 3));

    return 0;
}
