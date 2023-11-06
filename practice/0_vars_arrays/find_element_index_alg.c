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

    char array[ARR_LEN] = {0, 1, 2, 3, 4, 42, 6, 7, 8, 9};

    printf("initial array state\n");
    print_array(array, ARR_LEN);

    char element_to_find = 42;
    int index_found = 0;

    for(int i = 0; i < ARR_LEN; i++) {
        if(array[i] == element_to_find) {
            index_found = i;
        }
    }

    printf("found value %d at index %d \n", element_to_find, index_found);

    return 0;
}
