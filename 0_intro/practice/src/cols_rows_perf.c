#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_LEN 1000
// 1000 * 1000 * 8 bytes = ~7 MB, no way this fits in cache

#define NUM_ITERATIONS_PER_EXPERIMENT 100
#define NUM_EXPERIMENTS 10

int main() {
    long long arr[ARR_LEN][ARR_LEN];

    srand(42);

    for (int i = 0; i < ARR_LEN; i++) {
        for (int j = 0; j < ARR_LEN; j++) {
        arr[i][j] = rand();
        }
    }

    clock_t t;
    double time_taken;

    printf("\nexperiment - good\n");
    for (int n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock();

        long long exp_res_from_good;

        for (int iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            long long res = 0;

            for (int i = 0; i < ARR_LEN; i++) {
                for (int j = 0; j < ARR_LEN; j++) {
                long long current_el = arr[i][j];
                    if (current_el % 2 == 0) {
                        res -= current_el;
                    } else {
                        res += current_el;
                    }
                }
            }
        }

        t = clock() - t;

        time_taken = ((double)t) / CLOCKS_PER_SEC;
        printf("experiment %d: executed in %f seconds \n", n_exp, time_taken);
    }

    printf("\nexperiment - bad\n");
    for (int n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock();

        long long exp_res_from_bad;

        for (int iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            long long res = 0;

            for (int j = 0; j < ARR_LEN; j++) {
                for (int i = 0; i < ARR_LEN; i++) {
                    long long current_el = arr[i][j];
                    if (current_el % 2 == 0) {
                        res -= current_el;
                    } else {
                        res += current_el;
                    }
                }
            }
        }

        t = clock() - t;

        time_taken = ((double)t) / CLOCKS_PER_SEC;
        printf("experiment %d: executed in %f seconds \n", n_exp, time_taken);
    }

    return 0;
}
