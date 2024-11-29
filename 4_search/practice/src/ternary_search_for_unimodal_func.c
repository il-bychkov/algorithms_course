#include <stdio.h>

#define ARR_SIZE 1000
#define EXTREMUM_INDEX ARR_SIZE - ARR_SIZE / 3 + 14
#define VALUE_OFFSET 42


int ternary_search_for_unimodal_func(int* array, int size) {
    int left = 0;
    int right = size - 1;

    while (right - left > 2) {
        int left_third = left + (right - left) / 3;
        int right_third = right - (right - left) / 3;

        if (array[left_third] < array[right_third]) {
            left = left_third;
        } else {
            right = right_third;
        }
    }

    int max_index = left;

    if (array[max_index + 1] > array[max_index]) {
        max_index += 1;
    }

    if (array[right] > array[max_index]) {
        max_index = right;
    }

    return max_index;
}

int main() {
    int arr[ARR_SIZE];

    for (size_t i = 0; i <= EXTREMUM_INDEX; i++)
    {
        arr[i] = i + VALUE_OFFSET;
    }

    for (size_t i = EXTREMUM_INDEX + 1; i < ARR_SIZE; i++)
    {
        arr[i] = ARR_SIZE - i + VALUE_OFFSET;
    }

    printf("function extremum is: \n\n");
    printf("index: ... %d %d %d %d %d ...\n", EXTREMUM_INDEX - 2, EXTREMUM_INDEX - 1, EXTREMUM_INDEX, EXTREMUM_INDEX + 1, EXTREMUM_INDEX + 2);
    printf("value: ... %d %d %d %d %d ...\n", arr[EXTREMUM_INDEX - 2], arr[EXTREMUM_INDEX - 1], arr[EXTREMUM_INDEX], arr[EXTREMUM_INDEX + 1], arr[EXTREMUM_INDEX + 2]);

    int index = ternary_search_for_unimodal_func(arr, ARR_SIZE);

    printf("\n");
    printf("Found extremum at index %d\n", index);
}
