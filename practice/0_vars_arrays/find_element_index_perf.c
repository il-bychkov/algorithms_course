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

    printf("\nexperiment - find index of element\n");
    for(int n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock();

        int find_index = rand() % ARR_LEN;
        char element_to_find = array[find_index];

        for(int iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            int index_found = 0;

            for(int i = 0; i < ARR_LEN; i++) {
                if(array[i] == element_to_find) {
                    index_found = i;
                }
            }
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %d: %d founds of index %d executed in %f seconds \n", n_exp, NUM_ITERATIONS_PER_EXPERIMENT, find_index, time_taken);
    }

    return 0;
}
