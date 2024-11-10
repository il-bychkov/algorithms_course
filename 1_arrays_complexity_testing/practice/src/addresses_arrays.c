#include <stdio.h>

#define ARR_SIZE 10

int main() {
    // Initialize an array
    int intArray[ARR_SIZE] = {10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

    // Print an address of every array element
    for (int i = 0; i < ARR_SIZE; i++) {
        printf("int array element shift = [%d] -  value stored = %d  - address = %p\n", i, intArray[i], &intArray[i]);
    }
    return 0;
}
