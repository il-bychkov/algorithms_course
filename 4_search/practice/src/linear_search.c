#include <stdio.h>

#define ARR_SIZE 1000

int linear_search(int* array, int n, int x) {

    for (int i = 0; i < n; i++)
        if (array[i] == x) {
            return i;
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
    int index = linear_search(arr, ARR_SIZE, element);

    printf("Found element %d at index %d\n", element, index);

}
