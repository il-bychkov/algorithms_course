#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ARR_SIZE 10

// comment for skipping debug messages
#define DEBUG_MSG

void print_array_in_range(int64_t *arr, int64_t start, int64_t end) {
  if (start < end) {
    for (int i = start; i <= end; i++) {
      printf("%lld ", arr[i]);
    }
  }
  printf("\n");
}

void swap_in(int64_t *arr, size_t first, size_t second) {
  int64_t tmp = arr[first];
  arr[first] = arr[second];
  arr[second] = tmp;
}

size_t hoar_partition(int64_t *arr, size_t start, size_t end) {
  int64_t pivot = (arr[start] + arr[end]) / 2;
  size_t i = start, j = end;
  while (1) {
    // skip all elements less than pivot from start to end
    while (arr[i] < pivot) {
      ++i;
    };
    // skip all elements greater than pivot from end to start
    while (arr[j] > pivot) {
      --j;
    };
    // return when 'start' and 'end' reach each other or swaps
    if (i >= j) {
      return j;
    }
    // we reached swap condition
    swap_in(arr, i++, j--);
  }
}

void qucik_sort(int64_t *arr, int64_t start, int64_t end) {
#ifdef DEBUG_MSG
  printf("qucik_sort: [%lld:%lld] on ", start, end);
  print_array_in_range(arr, start, end);
#endif
  if (start < end) {
    size_t p = hoar_partition(arr, start, end);
    qucik_sort(arr, start, p);
    qucik_sort(arr, p + 1, end);
  }
}

int main() {
  int64_t arr[ARR_SIZE] = {3, 7, 8, 5, 2, 1, 9, 5, 0, 4};

  printf("Before sorting:\n");
  print_array_in_range(arr, 0, ARR_SIZE - 1);

  printf("Start sorting...\n");
  qucik_sort(arr, 0, ARR_SIZE - 1);

  printf("After sorting:\n");
  print_array_in_range(arr, 0, ARR_SIZE - 1);
}
