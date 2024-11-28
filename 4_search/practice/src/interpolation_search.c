#include <stdio.h>

#define ARR_SIZE 1000

int interpolation_search(int* arr, int n, int x)
{
    // Find indexes of two corners
    int low = 0, high = (n - 1);
    // Since array is sorted, an element present
    // in array must be in range defined by corner
    while (low <= high && x >= arr[low] && x <= arr[high])
    {
        if (low == high) {
            if (arr[low] == x) {
                return low;
            } else {
                return -1;
            }
        }
        // Probing the position with keeping
        // uniform distribution in mind.
        int pos = low + (((double)(high - low) /
            (arr[high] - arr[low])) * (x - arr[low]));

        // Condition of target found
        if (arr[pos] == x)
            return pos;
        // If x is larger, x is in upper part
        if (arr[pos] < x) {
            low = pos + 1;
        }
        // If x is smaller, x is in the lower part
        else {
            high = pos - 1;
        }
    }
    return -1;
}

int main() {
    int arr[ARR_SIZE];

    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        arr[i] = i;
    }

    int element = 831;
    int index = interpolation_search(arr, ARR_SIZE, element);

    printf("Found element %d at index %d\n", element, index);

}
