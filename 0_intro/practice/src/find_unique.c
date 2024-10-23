#include <stdio.h>


int main() {

    int arr[11] = {1, 3, 2, 2, 1, 3, 7, 9, 8, 8, 9};

    int unique = 0;

    for (size_t i = 0; i < sizeof(arr)/sizeof(arr[0]); i++){
        unique ^= arr[i];
    }

    printf("unique = %d\n", unique);

    return 0;
}
