#include <stdio.h>

#define ARR_LEN 10

void print_array(char* array, int array_len) {
    printf("[ ");
    for(int i = 0; i < array_len - 1; i++) {
        printf("%d, ", array[i]);
    }
    printf("%d ]\n", array[array_len - 1]);
}

int main() {

    char array[ARR_LEN] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    printf("initial array state\n");
    print_array(array, ARR_LEN);

    int delete_index = 4;

    for(int i = delete_index; i < ARR_LEN - 1; i++) {
        array[i] = array[i + 1];
    }

    array[ARR_LEN - 1] = 0;


    printf("array state after deleting value at index %d \n", delete_index);
    print_array(array, ARR_LEN);

    return 0;
}
