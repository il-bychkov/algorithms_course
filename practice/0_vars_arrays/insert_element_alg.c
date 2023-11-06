#include <stdio.h>

#define ARR_SIZE 11


// Function to print an array - it accepts pointer to the array's memory and array's size
void printArray(int* arr, int len)
{
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
	printf("\n");	
}

int main() 
{	
    // Initialize an array and variables - we assume the array has 1 free position at the end
    int array[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1};	
    int insertIndex = 4;
    int insertValue = 42;
	
	// Print the initial array 
    printf("Initial array:\n");	
	printArray(array, ARR_SIZE);
  
    // Insert element - move affected elements one position right
    for(int i = ARR_SIZE - 1; i > insertIndex; i--) {
		array[i] = array[i - 1];
    }
	// Insert a new value
	array[insertIndex] = insertValue;
	
	// Print the resulting array
	printf("Array after inserting value %d at index %d \n", insertValue, insertIndex);
	printArray(array, ARR_SIZE);
   
    return 0;
}
