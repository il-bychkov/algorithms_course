#include <stdio.h>
#include <stdint.h>

#define DIM_1_SIZE 3
#define DIM_2_SIZE 5

int main() {

    uint32_t arr[DIM_1_SIZE][DIM_2_SIZE] = {
        {1, 2, 3, 4, 5},
        {2, 3, 4, 5, 6},
        {3, 4, 5, 6, 7},
    };
    // expected output on this data:
    // rows sum: 15, 20, 25
    // cols sum: 6, 9, 12, 15, 18

    // trivial alg
    // iterate each col and count sum, then iterate each row and count sum (or first row and then col)
    // opearations count: 2(DIM_1_SIZE*DIM_2_SIZE)
    // also row read is bad for perf

    uint32_t sum_rows[DIM_1_SIZE] = {0};
    uint32_t sum_cols[DIM_2_SIZE] = {0};

    // one-pass alg
    for(int i = 0; i < DIM_1_SIZE; i++) {
        for(int j = 0; j < DIM_2_SIZE; j++) {
            sum_rows[i] += arr[i][j];
            sum_cols[j] += arr[i][j];
        }
    }
    // if data readed from stdin - no need to fill 2D array at all, can add straight to sum

    printf("rows sum:\n");

    for(int i = 0; i < DIM_1_SIZE; i++) {
        printf("%d ", sum_rows[i]);
    }
    printf("\n");

    printf("cols sum:\n");

    for(int i = 0; i < DIM_2_SIZE; i++) {
        printf("%d ", sum_cols[i]);
    }
    printf("\n");

    return 0;
}
