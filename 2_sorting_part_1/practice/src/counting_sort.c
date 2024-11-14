#include <stdio.h>
#include <stdlib.h>

void countSort(int inputArray[], int N) {

    // Finding the maximum element of
    // array inputArray[]
    int M = 0;
    for (int i = 0; i < N; i++)
        if (inputArray[i] > M)
            M = inputArray[i];

    // Initializing countArray[] with 0
    int* countArray = (int*)calloc(M + 1, sizeof(int));

    // Mapping each element of inputArray[]
    // as an index of countArray[] array
    for (int i = 0; i < N; i++)
        countArray[inputArray[i]]++;

    // Calculating prefix sum at every index
    // of array countArray[]
    for (int i = 1; i <= M; i++)
        countArray[i] += countArray[i - 1];

    // Creating outputArray[] from countArray[] array
    int* outputArray = (int*)malloc(N * sizeof(int));
    for (int i = N - 1; i >= 0; i--) {
        outputArray[countArray[inputArray[i]] - 1] = inputArray[i];
        countArray[inputArray[i]]--;
    }

    // Copying sorted elements back to inputArray[]
    for (int i = 0; i < N; i++)
        inputArray[i] = outputArray[i];

    // Freeing dynamically allocated memory
    free(countArray);
    free(outputArray);
}

// Driver code
int main() {

    // Input array
    int inputArray[] = {4, 3, 12, 1, 5, 5, 3, 9};
    int N = sizeof(inputArray) / sizeof(inputArray[0]);

    // Sorting the array
    countSort(inputArray, N);

    // Printing the sorted array
    for (int i = 0; i < N; i++)
        printf("%d ", inputArray[i]);

    return 0;
}
