#include <stdio.h>

#define ARR_SIZE 11

void print_array(int* arr)
{
    for(int i = 0; i < ARR_SIZE; i++) {
        printf("%d ", arr[i]);
    }
	printf("\n");	
}

int main() 
{	
    int array[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1};
	
    int insert_index = 4;
    int insert_value = 42;

    printf("Initial array:\n");	
	print_array(array);
  
		   
    for(int i = ARR_SIZE-1; i > insert_index; i--) {
		array[i] = array[i-1];
    }
	array[insert_index] = insert_value;
	
	printf("Array after inserting value %d at index %d \n", insert_value, insert_index);
	print_array(array);
   
    return 0;
}
