#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100

void arrayInsert(int *array, int value, int position) {
    // Start clock
    clock_t t = clock();
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for (int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++) {
        // Insert element - move affected elements one position right
        for (int j = ARR_SIZE - 1; j > position; j--) {
            array[j] = array[j - 1];
        }
        // Insert a new value
        array[position] = value;
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t) / CLOCKS_PER_SEC;
    printf("Experiment: %d is inserted to index %d. Time of %d runs = %f seconds \n", value, position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);
}

int main() {
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);

    // Fill an array with initial uniformly distributed random values (last
    // position is "free")
    for (int i = 0; i < ARR_SIZE - 1; i++) {
        array[i] = rand();
    }

    // Make 3 insertions - 0, middle and last positions
    int insertNumber = 42;
    arrayInsert(array, insertNumber, 0);
    arrayInsert(array, insertNumber, ARR_SIZE / 2);
    arrayInsert(array, insertNumber, ARR_SIZE - 1);
}
