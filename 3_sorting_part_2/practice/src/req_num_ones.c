#include <stdio.h>

int req_num_ones(int* arr, int len, int index) {
    if(len == index) {
        return 0;
    }

    if(arr[index] == 1) {
        return 1 + req_num_ones(arr, len, index + 1);
    } else {
        return 0 + req_num_ones(arr, len, index + 1);
    }
}

int main() {
    int arr[] = {1, 2, 3, 1, 1, 5, 6, 12};

    printf("%d\n", req_num_ones(arr, sizeof(arr)/sizeof(arr[1]), 0));
}
