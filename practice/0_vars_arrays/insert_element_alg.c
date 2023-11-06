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

    int insert_index = 4;
    char insert_value = 42;

    char old_element;
    char current_element = array[insert_index];
    array[insert_index] = insert_value;

    for(int i = insert_index + 1; i < ARR_LEN; i++) {
        old_element = array[i];
        array[i] = current_element;
        current_element = old_element;
    }


    printf("array state after inserting value %d at index %d \n", insert_value, insert_index);
    print_array(array, ARR_LEN);

    return 0;
}
