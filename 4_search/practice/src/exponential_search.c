#include <stdio.h>

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define ARR_SIZE 1000

int binary_search(int arr[], int l, int r, int x)
{
    if (r >= l)
    {
        int mid = l + (r - l)/2;

        // If the element is present at the middle
        // itself
        if (arr[mid] == x)
            return mid;

        // If element is smaller than mid, then it
        // can only be present n left subarray
        if (arr[mid] > x)
            return binary_search(arr, l, mid-1, x);

        // Else the element can only be present
        // in right subarray
        return binary_search(arr, mid+1, r, x);
    }

    // We reach here when element is not present
    // in array
    return -1;
}

int exponential_search(int* arr, int n, int x)
{
    // If x is present at first location itself
    if (arr[0] == x) {
        return 0;
    }

    // Find range for binary search by repeated doubling
    int i = 1;
    while (i < n && arr[i] <= x) {
        i = i*2;
    }

    //  Call binary search for the found range.
    return binary_search(arr, i/2, min(i, n-1), x);
}

int main() {
    int arr[ARR_SIZE];

    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        arr[i] = i;
    }

    int element = 831;
    int index = exponential_search(arr, ARR_SIZE, element);

    printf("Found element %d at index %d\n", element, index);

}
