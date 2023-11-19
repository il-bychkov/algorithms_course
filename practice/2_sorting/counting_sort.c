#include "sorting.h"

#define ARR_SIZE 10
#define LARGE_ARR_SIZE 100000
#define N_ITERATIONS   1000

// variant with prefix sum
// alg is stable, but slower than direct sorted array fill
void counting_sort_inc(uint32_t* array, size_t size) {
    uint32_t max_value = array[0];

    // search by largest element
    for (size_t i = 1; i < size; i++)
    {
        if(array[i] > max_value) {
            max_value = array[i];
        }
    }
    uint32_t count_array_size = max_value + 1;
    // allocate tmp arrays
    uint32_t* count_array = malloc(count_array_size * sizeof(uint32_t));
    uint32_t* sorted_array = malloc((size + 1) * sizeof(uint32_t));
    // clear count array
    for (size_t i = 0; i < count_array_size; i++)
    {
        count_array[i] = 0;
    }
    // count elements in unsorted array
    for (size_t i = 0; i < size; i++)
    {
        count_array[array[i]]++;
    }
    // calculate prefix sum
    for (size_t i = 1; i <= count_array_size - 1; i++) {
        count_array[i] += count_array[i - 1];
    }
    // fill sorted array
    // DO NOT USE size_t IN THIS CYCLE
    // or use with condition i != -1
    // i >= 0 works only with signed counter
    for (int i = size - 1; i >= 0; i--)
    {
        sorted_array[count_array[array[i]] - 1] = array[i];
        count_array[array[i]]--;
    }
    // copy sorted array
    for (size_t i = 0; i < size; i++)
    {
        array[i] = sorted_array[i];
    }

    free(count_array);
    free(sorted_array);
}

// variant vithout prefix sum
// bit faster, but not stable
void counting_sort_dec(uint32_t* array, size_t size) {
    uint32_t max_value = array[0];

    // search by largest element
    for (size_t i = 1; i < size; i++)
    {
        if(array[i] > max_value) {
            max_value = array[i];
        }
    }
    uint32_t count_array_size = max_value + 1;
    // allocate tmp arrays
    uint32_t* count_array = malloc(count_array_size * sizeof(uint32_t));
    // clear count array
    for (size_t i = 0; i < count_array_size; i++)
    {
        count_array[i] = 0;
    }
    // count elements in unsorted array
    for (size_t i = 0; i < size; i++)
    {
        count_array[array[i]]++;
    }
    // fill sorted array
    size_t result_array_index = size - 1;
    for (size_t i = 0; i < count_array_size; i++)
    {
        for (size_t j = count_array[i]; j > 0; j--)
        {
            array[result_array_index] = i;
            result_array_index--;
        }

    }

    free(count_array);
}

int main() {

    uint32_t array[ARR_SIZE];
    uint32_t array_sorted_ref[ARR_SIZE];

    // test sort smallest to largest
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);

    counting_sort_inc(array, ARR_SIZE);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);


    // test sort largest to smallest
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_dec(array_sorted_ref, ARR_SIZE);

    counting_sort_dec(array, ARR_SIZE);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);


    uint32_t large_array[LARGE_ARR_SIZE];


    clock_t t;
    double owerall_time_taken;

    printf("\ntest time smallest to largest\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 10);
        t = clock(); // hi-res clock counter
        counting_sort_inc(large_array, LARGE_ARR_SIZE);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-10, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        counting_sort_inc(large_array, LARGE_ARR_SIZE);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    printf("\ntest time largest to smallest\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 10);
        t = clock(); // hi-res clock counter
        counting_sort_dec(large_array, LARGE_ARR_SIZE);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-10, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        counting_sort_dec(large_array, LARGE_ARR_SIZE);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    return 0;
}
