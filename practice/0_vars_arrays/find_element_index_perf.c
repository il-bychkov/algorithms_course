#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100

void findElement(int *array, int target) {
  // Start clock
  clock_t t = clock();
  // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
  for (int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++) {
    // Actually this variable is used only to "save" answer
    int indexFound = -1;
    // For loop to find the target value
    for (int i = 0; i < ARR_SIZE; i++) {
      // If target is found - save index and leave
      if (array[i] == target) {
        indexFound = i;
        break;
      }
    }
  }
  // Finish clock, compute total time spent in seconds
  t = clock() - t;
  double timeSpent = ((double)t) / CLOCKS_PER_SEC;
  printf("Experiment: Element %d search . Time of %d runs = %f seconds \n",
         target, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);
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

  // Make 3 search requsts - first element array[0], middle element and last
  // element
  findElement(array, array[0]);
  findElement(array, array[ARR_SIZE / 2]);
  findElement(array, array[ARR_SIZE - 1]);

  return 0;
}