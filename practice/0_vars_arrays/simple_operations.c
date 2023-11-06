// may show students some compiler "magic" - compile with and without -O3 and show perf difference
// point attention to fixed seed random - no diff in data

#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define DIM1_SIZE_TEST 10
#define DIM1_SIZE_PERF 1000000
#define NUM_ITERATIONS_PER_EXPERIMENT 100
#define NUM_EXPERIMENTS 10

void print_array(uint8_t* array, size_t array_len) {
    printf("[ ");
    for(size_t i = 0; i < array_len - 1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d ]\n", array[array_len - 1]);
}

// may ask students how we can save element that will go outside arr bound after insert
// answer is by returning current_element
void insert_element(uint8_t* array, size_t array_len, size_t index, uint8_t element_to_insert) {
    uint8_t old_element;
    uint8_t current_element = array[index];
    array[index] = element_to_insert;

    for(size_t i = index + 1; i < array_len; i++) {
        old_element = array[i];
        array[i] = current_element;
        current_element = old_element;
    }
}

void delete_element(uint8_t* array, size_t array_len, size_t index) {
    for(size_t i = index; i < array_len - 1; i++) {
        array[i] = array[i + 1];
    }

    array[array_len - 1] = 0;
}

// may ask how to find last instead of first
size_t find_element_index(uint8_t* array, size_t array_len, uint8_t element_to_find) {
    for(size_t i = 0; i < array_len; i++) {
        if(array[i] == element_to_find) {
            return i;
        }
    }

    return array_len;
}

int main() {

    // define 1D array
    uint8_t array_test[DIM1_SIZE_TEST];
    uint8_t array_perf[DIM1_SIZE_PERF];

    // fill array with random data
    srand(42);

    for(size_t i = 0; i < DIM1_SIZE_TEST; i++) {
        array_test[i] = rand();
    }

    for(size_t i = 0; i < DIM1_SIZE_PERF; i++) {
        array_perf[i] = rand();
    }

    // alg tests
    printf("initial array state\n");
    print_array(array_test, DIM1_SIZE_TEST);

    size_t insert_index = 4;
    uint8_t insert_value = 42;

    insert_element(array_test, DIM1_SIZE_TEST, insert_index, insert_value);

    printf("array state after inserting value %d at index %ld \n", insert_value, insert_index);
    print_array(array_test, DIM1_SIZE_TEST);

    size_t delete_index = 5;

    delete_element(array_test, DIM1_SIZE_TEST, delete_index);

    printf("array state after deleting value at index %ld \n", delete_index);
    print_array(array_test, DIM1_SIZE_TEST);

    size_t index_found = find_element_index(array_test, DIM1_SIZE_TEST, insert_value);
    printf("found value %d at index %ld \n", insert_value, index_found);

    // prepare variables for time measurement
    clock_t t;
    double time_taken;

    printf("\nexperiment - insertion\n");
    // experiment idea: smaller index == greater time => linear complexity
    for(size_t n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock(); // hi-res clock counter

        size_t exp_insert_index = rand() % DIM1_SIZE_PERF;
        uint8_t exp_insert_value = 42;

        for(size_t iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            insert_element(array_perf, DIM1_SIZE_PERF, exp_insert_index, exp_insert_value);
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %ld: %d inserts to index %ld executed in %f seconds \n", n_exp, NUM_ITERATIONS_PER_EXPERIMENT, exp_insert_index, time_taken);
    }

    printf("\nexperiment - deletion\n");
    // experiment idea: smaller index == greater time => linear complexity
    for(size_t n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock(); // hi-res clock counter

        size_t exp_delete_index = rand() % DIM1_SIZE_PERF;

        for(size_t iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            delete_element(array_perf, DIM1_SIZE_PERF, exp_delete_index);
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %ld: %d deletions of index %ld executed in %f seconds \n", n_exp, NUM_ITERATIONS_PER_EXPERIMENT, exp_delete_index, time_taken);
    }

    printf("\nexperiment - find element index\n");
    // experiment idea: greater index == greater time => linear complexity
    for(size_t n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock(); // hi-res clock counter

        size_t exp_find_index = rand() % DIM1_SIZE_PERF;
        uint8_t element_to_find =  array_perf[exp_find_index];

        for(size_t iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            exp_find_index = find_element_index(array_perf, DIM1_SIZE_PERF, element_to_find);
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %ld: %d founds of index %ld executed in %f seconds \n", n_exp, NUM_ITERATIONS_PER_EXPERIMENT, exp_find_index, time_taken);
    }

    printf("\nexperiment - get element\n");
    // experiment idea: no correlation between time and index => constant complexity
    for(size_t n_exp = 0; n_exp < NUM_EXPERIMENTS; n_exp++) {
        t = clock(); // hi-res clock counter

        size_t exp_get_index = rand() % DIM1_SIZE_PERF;
        uint8_t element_to_find =  array_perf[exp_get_index];

        for(size_t iteration = 0; iteration < NUM_ITERATIONS_PER_EXPERIMENT * NUM_ITERATIONS_PER_EXPERIMENT; iteration++) {
            element_to_find = array_perf[exp_get_index];
        }

        t = clock() - t;

        time_taken = ((double)t)/CLOCKS_PER_SEC;
        printf("experiment %ld: %d accesses of index %ld executed in %f seconds \n", n_exp, NUM_ITERATIONS_PER_EXPERIMENT * NUM_ITERATIONS_PER_EXPERIMENT, exp_get_index, time_taken);
    }

    return 0;
}
