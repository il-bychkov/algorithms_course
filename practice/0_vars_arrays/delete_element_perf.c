#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_LEN 1000000
#define NUM_ITERATIONS_PER_EXPERIMENT 100
#define NUM_EXPERIMENTS 10

int main() {
    char array[ARR_LEN];

    srand(42);

    for(int i = 0; i < ARR_LEN; i++) {
        array[i] = rand();
    }

    clock_t t;
    double time_taken;

    int insert_index = 4;
    char insert_value = 42;


    printf("\nexperiment - deletion\n");
    for(int n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock();

        int delete_index = rand() % ARR_LEN;

        for(int iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {

            for(int i = delete_index; i < ARR_LEN - 1; i++) {
                array[i] = array[i + 1];
            }

            array[ARR_LEN - 1] = 0;
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %d: %d deletions of index %d executed in %f seconds \n", n_exp, NUM_ITERATIONS_PER_EXPERIMENT, delete_index, time_taken);
    }

    return 0;
}
