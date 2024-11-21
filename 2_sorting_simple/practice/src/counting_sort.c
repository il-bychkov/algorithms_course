#include <stdio.h>
#include <stdlib.h>

void countingSort(int* arr, int n) {

    int maxEl = arr[0];

    for (int i = 1; i < n; ++i) {
        if (arr[i] > maxEl) {
            maxEl = arr[i];
        }
    }

    int* countArr = (int*)calloc((maxEl + 1), sizeof(arr[0]));
    int* output = (int*)calloc(n, sizeof(arr[0]));

    for(int i = 0; i < n; ++i) {
        ++countArr[arr[i]];
    }

    int j = 0;

    for (int i = 0; i < maxEl + 1; ++i) {
        while (countArr[i] != 0) {
            output[j] = i;
            countArr[i]--;
            j++;
        }
    }

    for (int i = 0; i < 10; ++i) {
        arr[i] = output[i];
    }

    free(output);
    free(countArr);
}

void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

int main(void)
{
    int* a = (int*)calloc(10, sizeof(int));
    for (int i = 9; i >= 0; i--) {
        a[10-i] = i;
    }

    countingSort(a, 10);

    printArray(a, sizeof(a) / sizeof(a[0]));

    return 0;
}
