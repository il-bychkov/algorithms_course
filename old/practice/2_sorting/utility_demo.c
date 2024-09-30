#include "sorting.h"

#define ARR_SIZE 10

int main() {

    uint32_t array[ARR_SIZE];
    uint32_t array_sorted_ref[ARR_SIZE];

    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial unsorted array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);
    array_print(array_sorted_ref, ARR_SIZE, "\nreference sorted smallest to largest array state\n");

    array_sort_std_dec(array, ARR_SIZE);
    array_print(array, ARR_SIZE, "\ninitial sorted largest to smallest array state\n");

    array_test(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array, ARR_SIZE);
    array_print(array, ARR_SIZE, "\ninitial sorted smallest to largest array state\n");

    array_test(array_sorted_ref, array, ARR_SIZE);

    return 0;
}
