#include <stdio.h>

#define ARR_SIZE 10

// Function to print an array - it accepts pointer to the array's memory and array's size
void printArray(int* arr, int len)
{
    for(int i = 0; i < len; i++)
	{
        printf("%d ", arr[i]);
    }
	printf("\n");	
}

int main() {
	
	// Initialize an array and variables
    int array[ARR_SIZE] = {0, 11, 2, 33, 24, 5, 16, 37, 85, 99};	   
	// Target to find
    char elementToFind = 16;
	// Variable for resulting index, initialize it to some bad value to check if it is changed finally
    int indexFound = -1;
		
	// Print the initial array 
	printf("Initial array:\n");	
	printArray(array, ARR_SIZE);    
    
    // For loop to find the target value
    for(int i = 0; i < ARR_SIZE; i++) 
	{
		// If target is found - save index and leave
        if(array[i] == elementToFind) 
		{
            indexFound = i;
			break;
        }
    }
	
	// If this variable is not changed - element is missing
	if (indexFound != -1)
        printf("Element %d is found at index %d \n", elementToFind, indexFound);
	else
		printf("Element %d is not found\n", elementToFind, indexFound);

    return 0;
}
