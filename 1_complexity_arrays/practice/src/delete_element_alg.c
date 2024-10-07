#include <stdio.h>

#define ARR_SIZE 10

// Function to print an array - it accepts pointer to the array's memory and
// array's size
void printArray(int *arr, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    // Initialize an array and variables
    int array[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int deleteIndex = 4;
    int arrayActualLen = ARR_SIZE;

    // Print the initial array
    printf("Initial array:\n");
    printArray(array, ARR_SIZE);

    // Delete element - move affected elements one position left
    for (int i = deleteIndex + 1; i < ARR_SIZE; i++) {
      array[i - 1] = array[i];
    }

    // Change the array's actual length
    arrayActualLen--;

    // Print the resulting array
    printf("New array size = %d \n", arrayActualLen);
    printf("Array after deleting value at index %d \n", deleteIndex);
    printArray(array, arrayActualLen);

    return 0;
}
