#include "sorting.h"

void array_fill_rand(uint32_t* array, size_t array_size) {
    for(size_t i = 0; i < array_size; i++) {
        array[i] = rand();
    }
}

void array_fill_rand_range(uint32_t* array, size_t array_size, uint32_t range_start, uint32_t range_end) {
    for(size_t i = 0; i < array_size; i++) {
        array[i] = range_start + rand() % (range_end - range_start);
    }
}

static int comp_inc(const void * elem1, const void * elem2) {
    uint32_t f = *((uint32_t*)elem1);
    uint32_t s = *((uint32_t*)elem2);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

void array_sort_std_inc(uint32_t* array, size_t array_size) {
    qsort(array, array_size, sizeof(*array), comp_inc);
}

static int comp_dec(const void * elem1, const void * elem2) {
    uint32_t f = *((uint32_t*)elem1);
    uint32_t s = *((uint32_t*)elem2);
    if (f < s) return  1;
    if (f > s) return -1;
    return 0;
}

void array_sort_std_dec(uint32_t* array, size_t array_size) {
    qsort(array, array_size, sizeof(*array), comp_dec);
}

void array_copy(uint32_t* dst, uint32_t* src, size_t array_size) {
    for(size_t i = 0; i < array_size; i++) {
        dst[i] = src[i];
    }
}

int array_compare(uint32_t* a, uint32_t* b, size_t array_size) {
    for(size_t i = 0; i < array_size; i++) {
        if (a[i] != b[i]) {
            return i;
        }
    }

    return -1;
}

void array_print(uint32_t* array, size_t array_size, char* note) {

    for(size_t i = 0; note[i] != '\0' && i < 128; i++) {
        printf("%c",note[i]);
    }

    for(size_t i = 0; i < array_size - 1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d", array[array_size - 1]);

    printf("\n");
}

void array_test(uint32_t* ref, uint32_t* test, size_t array_size) {
    if (array_compare(ref, test, array_size) < 0) {
        printf("\nArrays are equal. Test passed.\n");
    } else {
        printf("\nArrays are not equal. Test falled.\n");
        array_print(ref, array_size, "reference array:\n");
        array_print(test, array_size, "tested array:\n");
    }
}
