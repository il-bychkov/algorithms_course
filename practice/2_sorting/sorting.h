#ifndef SORTING_UTILS_H
#define SORTING_UTILS_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// fill array randomly
void array_fill_rand(uint32_t* array, size_t array_size);
// fill array randomly with elements within range
void array_fill_rand_range(uint32_t* array, size_t array_size, uint32_t range_start, uint32_t range_end);
// sort array with qsort from stdlib, smallest to largest
// use it to validate own sorting algs implementations
void array_sort_std_inc(uint32_t* array, size_t array_size);
// sort array with qsort from stdlib, largest to smallest
// use it to validate own sorting algs implementations
void array_sort_std_dec(uint32_t* array, size_t array_size);
// coppy all items from src to dst
void array_copy(uint32_t* dst, uint32_t* src, size_t array_size);
// compare two arrays
// returns -1 if arrays are equal
// returns diff element index if arrays are not equal
int array_compare(uint32_t* a, uint32_t* b, size_t array_size);
// print array
// note is limited to 128 characters
void array_print(uint32_t* array, size_t array_size, char* note);
// compare two arrays and reports if it equal or not
// use it to validate own sorting algs implementations
void array_test(uint32_t* ref, uint32_t* test, size_t array_size);

#endif
