// note: compile with -Wformat=0 to ommit printf %X warning

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM1_SIZE 10
#define DIM2_SIZE 10

int main() {

    // define 1D arrays with different element types
    uint8_t char_array[DIM1_SIZE];
    uint32_t int_array[DIM1_SIZE];
    uint64_t longlong_array[DIM1_SIZE];

    // define 2D arrays with different element types
    uint8_t char_array_2d[DIM1_SIZE][DIM2_SIZE];
    uint32_t int_array_2d[DIM1_SIZE][DIM2_SIZE];
    uint64_t longlong_array_2d[DIM1_SIZE][DIM2_SIZE];

    // fill arrays with random data
    srand(42);

    for(size_t i = 0; i < DIM1_SIZE; i++) {
        char_array[i] = rand();
        int_array[i] = rand();
        longlong_array[i] = rand();
    }

    for(size_t i = 0; i < DIM1_SIZE; i++) {
        for(size_t j = 0; j < DIM2_SIZE; j++) {
            char_array_2d[i][j] = rand();
            int_array_2d[i][j] = rand();
            longlong_array_2d[i][j] = rand();
        }
    }

    // print element addresses
    printf("index, char_array addr, int_array addr, longlong_array addr\n");

    for(size_t i = 0; i < DIM1_SIZE; i++) {
        printf("[%d], 0x%X, 0x%X, 0x%X\n", i, &char_array[i], &int_array[i], &longlong_array[i]);
    }

    printf("\nindex, char_array addr, int_array addr, longlong_array addr\n");

    for(size_t i = 0; i < DIM1_SIZE; i++) {
        for(size_t j = 0; j < DIM2_SIZE; j++) {
            printf("[%d][%d], 0x%X, 0x%X, 0x%X\n", i, j, &char_array_2d[i][j], &int_array_2d[i][j], &longlong_array_2d[i][j]);
        }
    }

    return 0;
}
