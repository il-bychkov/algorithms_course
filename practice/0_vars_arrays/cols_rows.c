#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM1_SIZE 1000
#define DIM2_SIZE 1000
// 1000 * 1000 * 8 bytes = ~7 MB, no way this fits in cache

#define NUM_ITERATIONS_PER_EXPERIMENT 100
#define NUM_EXPERIMENTS 10

int64_t good_mem_access(int64_t* arr, size_t dim_1_size, size_t dim_2_size) {
    int64_t res = 0;

    for(size_t i = 0; i < dim_1_size; i++) {
        for(size_t j = 0; j < dim_2_size; j++) {
            int64_t current_el = arr[i * dim_1_size + j];
            if (current_el % 2 == 0) {
                res -= current_el;
            } else {
               res += current_el;
            }
        }
    }

    return res;
}

int64_t bad_mem_access(int64_t* arr, size_t dim_1_size, size_t dim_2_size) {
    int64_t res = 0;

    for(size_t j = 0; j < dim_2_size; j++) {
        for(size_t i = 0; i < dim_1_size; i++) {
            int64_t current_el = arr[i * dim_1_size + j];
            if (current_el % 2 == 0) {
                res -= current_el;
            } else {
               res += current_el;
            }
        }
    }

    return res;
}

int main() {
    int64_t arr[DIM1_SIZE][DIM2_SIZE];

    // fill arrays with random data
    srand(42);

    for(size_t i = 0; i < DIM1_SIZE; i++) {
        for(size_t j = 0; j < DIM2_SIZE; j++) {
            arr[i][j] = rand();
        }
    }

    int64_t res_from_good = good_mem_access((int64_t*)arr, DIM1_SIZE, DIM2_SIZE);
    int64_t res_from_bad = bad_mem_access((int64_t*)arr, DIM1_SIZE, DIM2_SIZE);

    printf("res from good: %ld\n", res_from_good);
    printf("res from bad: %ld\n", res_from_bad);

    // prepare variables for time measurement
    clock_t t;
    double time_taken;

    printf("\nexperiment - good\n");
    for(size_t n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock(); // hi-res clock counter

        int64_t exp_res_from_good;

        for(size_t iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            exp_res_from_good = good_mem_access((int64_t*)arr, DIM1_SIZE, DIM2_SIZE);
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %ld: executed in %f seconds \n", n_exp, time_taken);
    }

    printf("\nexperiment - bad\n");
    for(size_t n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock(); // hi-res clock counter

        int64_t exp_res_from_bad;

        for(size_t iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            exp_res_from_bad = bad_mem_access((int64_t*)arr, DIM1_SIZE, DIM2_SIZE);
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %ld: executed in %f seconds \n", n_exp, time_taken);
    }


    return 0;
}
