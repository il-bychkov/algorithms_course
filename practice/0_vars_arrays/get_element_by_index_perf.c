#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100

void getElement(int* array, int position)
{
	// Start clock
	clock_t t = clock();    
	// Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
	{
		// Variable where we read the data from the array		
		int elementValue = 0;
		// Read element at the position        
	    // Actually this variable it is not used
        // we need it only to read the value and compute total time
		elementValue = array[position];          	
    }
	// Finish clock, compute total time spent in seconds
    t = clock() - t;
	double timeSpent = ((double)t)/CLOCKS_PER_SEC;
	printf("Experiment: Read value at index %d. Time of %d runs = %f seconds \n", position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main() {
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
	
	// Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++) 
	{
        array[i] = rand();
    }	
	
	// Make 3 reads - 0, middle and last positions	
    getElement(array, 0);
	getElement(array, ARR_SIZE / 2);
	getElement(array, ARR_SIZE - 1);
	    
    return 0;
}
