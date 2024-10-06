#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100

void arrayDelete(int *array, int position) {
    // Start clock
    clock_t t = clock();
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for (int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++) {
        // Delete element - move affected elements one position left
        for (int i = position + 1; i < ARR_SIZE; i++) {
            array[i - 1] = array[i];
        }
        // Here we do not need to make a variable for actual lenghtChange
        // since it is not used here, we need only the time
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t) / CLOCKS_PER_SEC;
    printf("Experiment: Value at index %d is deleted. Time of %d runs = %f seconds \n", position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);
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

    // Make 3 deletions - 0, middle and last positions
    arrayDelete(array, 0);
    arrayDelete(array, ARR_SIZE / 2);
    arrayDelete(array, ARR_SIZE - 1);

  return 0;
}
