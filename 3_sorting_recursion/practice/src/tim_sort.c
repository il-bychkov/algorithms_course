#include<stdio.h>

#define min(a, b) (((a) < (b))? (a) : (b))

void insertionSort(int arr[], int l, int r)
{
    for (int i = l; i <= r; ++i) {
        int key = arr[i];
        int j = i - 1;

        /* Move elements of arr[0..i-1], that are
           greater than key, to one position ahead
           of their current position */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

/* A utility function to print array of size n */
void printArray(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        printf("%d ", arr[i]);
    printf("\n");
}

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Create temp arrays
    int* L = malloc(n1 * sizeof(int));
    int* R = malloc(n2 * sizeof(int));

    // Copy data to temp arrays L[] and R[]
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    // Merge the temp arrays back into arr[l..r
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        }
        else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    // Copy the remaining elements of L[],
    // if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    // Copy the remaining elements of R[],
    // if there are any
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    free(L);
    free(R);
}
// The best minrun is in [32, 64] or log_2 (n / minrun) = natural number
int GetMinrun(int n)
{
    int r = 0; // Is number has remainder from the division
    while (n >= 64) {
        r |= n & 1; // Checking least significant digit. If there is 1 then remainder is not 0.
        n >>= 1; // Divide n by 2
    }
    return n + r;
}

void timSort(int arr[], int n) {
    int minrun = GetMinrun(n);

    //Divide the array into runs
    for (int i = 0; i < n; i+= minrun) {
        insertionSort(arr, i, min(i + minrun - 1, n - 1));
    }

    //Merging
    //Firstly merge minrun parts into 2 * minrun parts, then 2 * minrun parts into 4 * minrun parts while size of part < n
    for (int size = minrun; size < n; size *= 2) {
        for (int left = 0; left < n; left += 2 * size) {
            //merging part[left, left + size - 1] and part[left + size, left + 2 * size - 1]
            int mid = left + size - 1;
            int right = min(mid + 1 + size - 1, n - 1);

            //if right is not empty so we can merge
            if (mid < right) {
                merge(arr, left, mid, right);
            }
        }
    }

}

int main() {
    int arr[] = { 12, 11, 13, 5, 6, 7, 1, 2 , 3, 4, 5, 6, 7, 8, 9, 10, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 31, 36, 27, 17, 4, 28, 37, 13, 9, 21, 44, 45, 15, 1, 5, 6, 32, 49, 18, 26, 10, 38, 14, 29, 33, 39, 8, 24, 25, 22, 12, 30, 34, 11, 2, 16, 40, 23, 43, 48, 41, 20, 7, 42, 46, 35, 3, 50, 47, 19 };
    int arr_size = sizeof(arr) / sizeof(arr[0]);

    printf("Given array is \n");
    printArray(arr, arr_size);

    timSort(arr, arr_size);

    printf("\nSorted array is \n");
    printArray(arr, arr_size);
    return 0;
}
