#include "../2_sorting/sorting.h"

int linear_search(uint32_t* array, int size, uint32_t item_to_find) {
    for (int i = 0; i < size; i++)
    {
        if (array[i] == item_to_find)
        {
            return i;
        }

    }
    return -1;
}

#define N_ITERATIONS 100000

int main() {

    srand(time(NULL));

    uint32_t array[DEFAULT_ARR_SIZE];

    array_fill_rand_range(array, DEFAULT_ARR_SIZE, 0, DEFAULT_ARR_SIZE);
    array_sort_std_inc(array, DEFAULT_ARR_SIZE);

    array_print(array, DEFAULT_ARR_SIZE, "array state\n");

    int index_to_find_item = rand() % DEFAULT_ARR_SIZE;

    int found_undex = linear_search(array, DEFAULT_ARR_SIZE, array[index_to_find_item]);

    printf("Element %d found at index %d\n", array[index_to_find_item], found_undex);


    clock_t t;
    double owerall_time_taken;

    printf("\ntest time linear search\n");

    uint32_t large_array[DEFAULT_LARGE_ARR_SIZE];

    array_fill_rand_range(large_array, DEFAULT_LARGE_ARR_SIZE, 0, DEFAULT_LARGE_ARR_SIZE);
    array_sort_std_inc(large_array, DEFAULT_LARGE_ARR_SIZE);

    owerall_time_taken = 0;
    for (int i = 0; i < N_ITERATIONS; i++)
    {
        int index_to_find_item = rand() % DEFAULT_LARGE_ARR_SIZE;
        t = clock(); // hi-res clock counter
        int found_undex = linear_search(large_array, DEFAULT_LARGE_ARR_SIZE, large_array[index_to_find_item]);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("%d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    return 0;
}
