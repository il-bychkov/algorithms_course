#include <stdio.h>
#include <math.h>

#define ARR_SIZE 1000

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

int main() {
    int arr[ARR_SIZE];

    for (size_t i = 0; i < ARR_SIZE; i++)
    {
        arr[i] = i;
    }

    int element = 831;
    int index = jump_search(arr, ARR_SIZE, element);

    printf("Found element %d at index %d\n", element, index);

}
