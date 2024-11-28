#include <stdio.h>

#define ARR_SIZE 1000

int binary_search(int* array, int size, int item_to_find) {
    int l = 0;
    int r = size - 1;
    while (l <= r) {
        int m = l + (r - l) / 2;
        // Check if x is present at mid
        if (array[m] == item_to_find) {
            return m;
        }
        // If x greater, ignore left half
        if (array[m] < item_to_find) {
            l = m + 1;
        }
        // If x is smaller, ignore right half
        else {
            r = m - 1;
        }
    }

    // If we reach here, then element was not present
    return -1;
}

int main() {
    int arr[ARR_SIZE];

    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        arr[i] = i;
    }

    int element = 831;
    int index = binary_search(arr, ARR_SIZE, element);

    printf("Found element %d at index %d\n", element, index);

}
