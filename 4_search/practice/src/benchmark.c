#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define ARR_SIZE 2000000
#define N_ITERATIONS 10000000

int min(int a, int b) {
    if(b>a)
      return a;
      else
      return b;
}

// algs under test

int linear_search(int* array, int n, int x) {

    for (int i = 0; i < n; i++)
        if (array[i] == x) {
            return i;
        }
    return -1;
}

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

int _ternary_search(int* ar, int l, int r, int key) {
    while (r >= l) {

        // Find the mid1 and mid2
        int mid1 = l + (r - l) / 3;
        int mid2 = r - (r - l) / 3;

        // Check if key is present at any mid
        if (ar[mid1] == key) {
            return mid1;
        }
        if (ar[mid2] == key) {
            return mid2;
        }

        // Since key is not present at mid,
        // check in which region it is present
        // then repeat the Search operation
        // in that region

        if (key < ar[mid1]) {

            // The key lies in between l and mid1
            r = mid1 - 1;
        }
        else if (key > ar[mid2]) {

            // The key lies in between mid2 and r
            l = mid2 + 1;
        }
        else {

            // The key lies in between mid1 and mid2
            l = mid1 + 1;
            r = mid2 - 1;
        }
    }

    // Key not found
    return -1;
}

int ternary_search(int* array, int size, int item_to_find) {
    return _ternary_search(array, 0, size, item_to_find);
}

int iterative_binary_search(int* array, int l, int r, int item_to_find) {
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

int exponential_search_w_iterative_binary_search(int* array, int size, int item_to_find)
{
    if (size == 0) {
        return -1;
    }

    int bound = 1;

    while (bound < size && array[bound] < item_to_find) {
        bound *= 2;
    }

    return iterative_binary_search(array, bound/2, (bound < size - 1) ? bound : size - 1, item_to_find);
}

int recursive_binary_search(int* array, int low, int high, int item_to_find)
{
    if (low > high) {
        return -1;
    }

    int mid = (low + high)/2;

    if (item_to_find == array[mid]) {
        return mid;
    }

    else if (item_to_find < array[mid]) {
        return recursive_binary_search(array, low, mid - 1, item_to_find);
    }

    else {
        return recursive_binary_search(array, mid + 1, high, item_to_find);
    }
}

int exponential_search_w_recursive_binary_search(int* array, int size, int item_to_find)
{
    if (size == 0) {
        return -1;
    }

    int bound = 1;

    while (bound < size && array[bound] < item_to_find) {
        bound *= 2;
    }

    return recursive_binary_search(array, bound/2, (bound < size - 1) ? bound : size - 1, item_to_find);
}

int interpolation_search(int* arr, int n, int x)
{
    // Find indexes of two corners
    int low = 0, high = (n - 1);
    // Since array is sorted, an element present
    // in array must be in range defined by corner
    while (low <= high && x >= arr[low] && x <= arr[high])
    {
        if (low == high) {
            if (arr[low] == x) {
                return low;
            } else {
                return -1;
            }
        }
        // Probing the position with keeping
        // uniform distribution in mind.
        int pos = low + (((double)(high - low) /
            (arr[high] - arr[low])) * (x - arr[low]));

        // Condition of target found
        if (arr[pos] == x) {
            return pos;
        }
        // If x is larger, x is in upper part
        if (arr[pos] < x) {
            low = pos + 1;
        }
        // If x is smaller, x is in the lower part
        else {
            high = pos - 1;
        }
    }
    return -1;
}

int jump_search(int* a, int n, int item) {
   int i = 0;
   int m = sqrt(n); //initializing block size= √(n)

    while(a[m] <= item && m < n) {
        // the control will continue to jump the blocks
        i = m;  // shift the block
        m += sqrt(n);
        if(m > n - 1)  // if m exceeds the array size
            return -1;
    }

    for(int x = i; x<m; x++) { //linear search in current block
        if(a[x] == item)
            return x; //position of element being searched
    }

    return -1;
}

double benchmark(int (*search)(int*, int, int), int* array, int array_size, int n_iterations) {

    clock_t t;
    double owerall_time_taken = 0;


    owerall_time_taken = 0;
    for (int i = 0; i < n_iterations; i++)
    {
        int index_to_find_item = rand() % ARR_SIZE;

        t = clock(); // hi-res clock counter
        int found_undex = search(array, array_size, array[index_to_find_item]);
        t = clock() - t;

        double time_taken = ((double)t) / CLOCKS_PER_SEC; // in seconds
        owerall_time_taken += time_taken;
    }

    return owerall_time_taken / n_iterations;
}

int main() {
    srand(time(NULL));

    int array[ARR_SIZE];

    for (size_t i = 0; i < ARR_SIZE; i++) {
        array[i] = i;
    }

    printf("╔═══════════════════════════════════════════════════════════════════════════════════════╗\n");
    printf("║ Search algs comparison benchmark                                                      ║\n");
    printf("╠══════════════════════════════════════╤════════════════════════════════════════════════╣\n");
    printf("║ Array size                           │ %d                                        ║\n", ARR_SIZE);
    printf("╟──────────────────────────────────────┼────────────────────────────────────────────────╢\n");
    printf("║ Number of iterations for O( N ) algs │ %d                                          ║\n", N_ITERATIONS / 1000);
    printf("╟──────────────────────────────────────┼────────────────────────────────────────────────╢\n");
    printf("║ Number of iterations for other algs  │ %d                                       ║\n", N_ITERATIONS);
    printf("╚══════════════════════════════════════╧════════════════════════════════════════════════╝\n");
    printf("\n");
    printf("┌─────────────────────────┬──────────────────────────┬──────────────────────────────────┐\n");
    printf("│ Search                  │ Computational complexity │ Mean time per 1 search operation │\n");
    printf("├─────────────────────────┼──────────────────────────┼──────────────────────────────────┤\n");
    printf("│ Binary search           │ O( log N )               │ %1.8lf                       │\n", benchmark(binary_search, array, ARR_SIZE, N_ITERATIONS));
    printf("├─────────────────────────┼──────────────────────────┼──────────────────────────────────┤\n");
    printf("│ Ternary search          │ O( 2 * log3 N )          │ %1.8lf                       │\n", benchmark(ternary_search, array, ARR_SIZE, N_ITERATIONS));
    printf("├─────────────────────────┼──────────────────────────┼──────────────────────────────────┤\n");
    printf("│ Exponential search with │ O( log N )               │ %1.8lf                       │\n", benchmark(exponential_search_w_iterative_binary_search, array, ARR_SIZE, N_ITERATIONS));
    printf("│ iterative binary search │                          │                                  │\n");
    printf("├─────────────────────────┼──────────────────────────┼──────────────────────────────────┤\n");
    printf("│ Exponential search with │ O( log N )               │ %1.8lf                       │\n", benchmark(exponential_search_w_recursive_binary_search, array, ARR_SIZE, N_ITERATIONS));
    printf("│ recursive binary search │                          │                                  │\n");
    printf("├─────────────────────────┼──────────────────────────┼──────────────────────────────────┤\n");
    printf("│ Interpolation search    │ O( log( log N ) )        │ %1.8lf                       │\n", benchmark(interpolation_search, array, ARR_SIZE, N_ITERATIONS));
    printf("├─────────────────────────┼──────────────────────────┼──────────────────────────────────┤\n");
    printf("│ Jump search             │ O( ?N )                  │ %1.8lf                       │\n", benchmark(jump_search, array, ARR_SIZE, N_ITERATIONS / 1000));
    printf("├─────────────────────────┼──────────────────────────┼──────────────────────────────────┤\n");
    printf("│ Linear search           │ O( N )                   │ %1.8lf                       │\n", benchmark(linear_search, array, ARR_SIZE, N_ITERATIONS / 1000));
    printf("└─────────────────────────┴──────────────────────────┴──────────────────────────────────┘\n");

}

