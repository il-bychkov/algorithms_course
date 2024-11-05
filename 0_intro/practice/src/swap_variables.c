#include <stdio.h>
#include <stdint.h>

// - пример обмена значениями (числа + произвольные биты)

void swap_add_sub(int* x, int* y) {

    *x = *x + *y; // x = x + y
    *y = *x - *y; // y = (x + y) - y = x
    *x = *x - *y; // x = x + y - x = y
}

void swap_xor(int* x, int* y) {
    *x = *x ^ *y; // x = x ^ y
    *y = *x ^ *y; // y = (x ^ y) ^ y = x
    *x = *x ^ *y; // x = (x ^ y) ^ x = y
}

void swap_xor_array(void* x, void* y, int bytelen) {
    // need explicit size types here
    uint8_t* p_x = (char*)x;
    uint8_t* p_y = (char*)y;

    for (size_t i = 0; i < bytelen; i++) {
        p_x[i] = p_x[i] ^ p_y[i]; // x = x ^ y
        p_y[i] = p_x[i] ^ p_y[i]; // y = (x ^ y) ^ y = x
        p_x[i] = p_x[i] ^ p_y[i]; // x = (x ^ y) ^ x = y
    }

}

// mul div swap also exists, but ommitted here because it is uneffective

int main() {
    int x = 128;
    int y = 345;

    int* p_x = &x;
    int* p_y = &y;

    printf("initial values\n");
    printf("%d, %d\n", x, y);

    swap_add_sub(p_x, p_y);

    printf("values after swap_add_sub\n");
    printf("%d, %d\n", x, y);

    swap_xor_array(p_x, p_y, sizeof(int));

    printf("values after swap_xor\n");
    printf("%d, %d\n", x, y);


    return 0;
}
