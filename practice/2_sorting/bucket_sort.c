#include "sorting.h"

#define ARR_SIZE 10
#define LARGE_ARR_SIZE 10000
#define N_ITERATIONS   10

void insertion_sort(uint32_t* array, size_t size)
{
    size_t j;
    for (size_t i = 1; i < size; i++) {
        uint32_t key = array[i];
        j = i - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j >= 0 && array[j] > key) {
            array[j + 1] = array[j];
            j = j - 1;
        }
        array[j + 1] = key;
    }
}

void bucket_sort(uint32_t* array, size_t size, uint32_t range_start, uint32_t range_end, size_t n_buckets) {
    uint32_t** buckets = malloc(n_buckets * sizeof(uint32_t*));
    size_t* buckets_size = malloc(n_buckets * sizeof(size_t));
    uint32_t* bucket_borders = malloc(n_buckets * sizeof(uint32_t));

    uint32_t bucket_range_step = (range_end - range_start) / n_buckets + 1;

    for (size_t i = 0; i < n_buckets; i++)
    {
        buckets[i] = malloc(size * sizeof(uint32_t));
        buckets_size[i] = 0;
        bucket_borders[i] = range_start + bucket_range_step * i;
    }

    for (size_t i = 0; i < size; i++)
    {
        size_t bucket_index = array[i] / bucket_range_step;
        buckets[bucket_index][buckets_size[bucket_index]] = array[i];
        buckets_size[bucket_index] += 1;
    }

    size_t output_array_offset = 0;

    for (size_t i = 0; i < n_buckets; i++)
    {
        insertion_sort(buckets[i], buckets_size[i]);

        for (size_t j = 0; j < buckets_size[i]; j++)
        {
            array[output_array_offset + j] = buckets[i][j];
        }

        output_array_offset += buckets_size[i];
    }
}

int main() {

    uint32_t array[ARR_SIZE];
    uint32_t array_sorted_ref[ARR_SIZE];

    // test sort smallest to largest 1 bucket
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);

    bucket_sort(array, ARR_SIZE, 0, 10, 1);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);

    // test sort smallest to largest 2 buckets
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);

    bucket_sort(array, ARR_SIZE, 0, 10, 2);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);

    // test sort smallest to largest 4 buckets
    array_fill_rand_range(array, ARR_SIZE, 0, 10);

    array_print(array, ARR_SIZE, "initial array state\n");

    array_copy(array_sorted_ref, array, ARR_SIZE);

    array_sort_std_inc(array_sorted_ref, ARR_SIZE);

    bucket_sort(array, ARR_SIZE, 0, 10, 4);

    printf("test small array\n");
    array_test(array_sorted_ref, array, ARR_SIZE);


    uint32_t large_array[LARGE_ARR_SIZE];


    clock_t t;
    double owerall_time_taken;

    printf("\ntest time 1 bucket\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        bucket_sort(large_array, LARGE_ARR_SIZE, 0, 1000, 1);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    printf("\ntest time 2 bucket\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        bucket_sort(large_array, LARGE_ARR_SIZE, 0, 1000, 2);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    printf("\ntest time 4 bucket\n");

    owerall_time_taken = 0;
    for (size_t i = 0; i < N_ITERATIONS; i++)
    {
        array_fill_rand_range(large_array, LARGE_ARR_SIZE, 0, 1000);
        t = clock(); // hi-res clock counter
        bucket_sort(large_array, LARGE_ARR_SIZE, 0, 1000, 4);
        t = clock() - t;
        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }
    printf("range 0-1000, %d iterations, executed in %f seconds \n", N_ITERATIONS, owerall_time_taken);

    return 0;
}
