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


    printf("\nexperiment - insertion\n");
    for(int n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock();

        int insert_index = rand() % ARR_LEN;
        char insert_value = 42;

        for(int iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {

            char old_element;
            char current_element = array[insert_index];
            array[insert_index] = insert_value;

            for(int i = insert_index + 1; i < ARR_LEN; i++) {
                old_element = array[i];
                array[i] = current_element;
                current_element = old_element;
            }
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %ld: %d inserts to index %d executed in %f seconds \n", n_exp, NUM_ITERATIONS_PER_EXPERIMENT, insert_index, time_taken);
    }

    return 0;
}
