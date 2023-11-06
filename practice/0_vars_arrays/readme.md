# Practice 0 - Addresses, variables and arrays

### Section 0: Introduction to translation & C compilation
- Translation: compilers and interpreters
- What happens inside IDE: how code is transformed into machine code
### Section 1: Addresses and variables
Source: addresses.c
```c 
#include <stdio.h>
int main()
{
    // Create 4 variables of different types
    int intVariable = 30;
    float floatVariable = 1.1;
    double doubleVariable = 1.1;
    char charVariable = 'c';
    
    printf("int start address = %p\n",&intVariable);
    printf("int size          = %lu\n",sizeof(int));
    // Int variable - address + 1 = address + one int
    printf("int end address   = %p\n\n",&intVariable + 1);

    printf("float start address = %p\n",&floatVariable);
    printf("float size          = %lu\n",sizeof(floatVariable));
    // Float variable - address + 1 = address + one float
    printf("float end   address = %p\n\n",&floatVariable + 1);

    printf("double start address = %p\n",&doubleVariable);
    printf("double size          = %lu\n",sizeof(doubleVariable));
    // Double variable - address + 1 = address + one double
    printf("double end address   = %p\n\n",&doubleVariable + 1);

    printf("char start address = %p\n",&charVariable);
    printf("char size          = %lu\n",sizeof(charVariable));
    // Char variable - address + 1 = address + one char
    printf("char end   address = %p\n\n",&charVariable + 1);
}
```

Output: addresses.c
```bash
$ ./a.out 
int start address = 0x7ffeed9c5b4c
int size          = 4
int end address   = 0x7ffeed9c5b50

float start address = 0x7ffeed9c5b48
float size          = 4
float end   address = 0x7ffeed9c5b4c

double start address = 0x7ffeed9c5b40
double size          = 8
double end address   = 0x7ffeed9c5b48

char start address = 0x7ffeed9c5b3f
char size          = 1
char end   address = 0x7ffeed9c5b40
```

### Section 1: Addresses and arrays

Source: addresses_arrays.c

```c 
#include <stdio.h>

#define ARR_SIZE 10

int main()
{
    // Initialize an array
    int intArray[ARR_SIZE] = {10, 11, 12, 13 ,14 ,15 ,16 ,17, 18, 19};

    // Print an address of every array element
    for (int i = 0; i < ARR_SIZE; i++)
        printf("int array element shift = [%d] -  value stored = %d  - address = %p\n",i, intArray[i], &intArray[i]);
    return 0;
}
```
Output: addresses.c
```bash
$ ./a.out 
int array element shift = [0] -  value stored = 10  - address = 0x7ffee9b45b20
int array element shift = [1] -  value stored = 11  - address = 0x7ffee9b45b24
int array element shift = [2] -  value stored = 12  - address = 0x7ffee9b45b28
int array element shift = [3] -  value stored = 13  - address = 0x7ffee9b45b2c
int array element shift = [4] -  value stored = 14  - address = 0x7ffee9b45b30
int array element shift = [5] -  value stored = 15  - address = 0x7ffee9b45b34
int array element shift = [6] -  value stored = 16  - address = 0x7ffee9b45b38
int array element shift = [7] -  value stored = 17  - address = 0x7ffee9b45b3c
int array element shift = [8] -  value stored = 18  - address = 0x7ffee9b45b40
int array element shift = [9] -  value stored = 19  - address = 0x7ffee9b45b44
```
### Section 2: Array: insert an element + measure the performance

Source: insert_element_alg.c

```c
#include <stdio.h>

#define ARR_SIZE 11


// Function to print an array - it accepts pointer to the array's memory and array's size
void printArray(int* arr, int len)
{
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");    
}

int main() 
{    
    // Initialize an array and variables - we assume the array has 1 free position at the end
    int array[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, -1};    
    int insertIndex = 4;
    int insertValue = 42;
    
    // Print the initial array 
    printf("Initial array:\n");    
    printArray(array, ARR_SIZE);
  
    // Insert element - move affected elements one position right
    for(int i = ARR_SIZE - 1; i > insertIndex; i--) {
        array[i] = array[i - 1];
    }
    // Insert a new value
    array[insertIndex] = insertValue;
    
    // Print the resulting array
    printf("Array after inserting value %d at index %d \n", insertValue, insertIndex);
    printArray(array, ARR_SIZE);
   
    return 0;
}

```

Output: insert_element_alg.c
```bash
Initial array:
0 1 2 3 4 5 6 7 8 9 -1
Array after inserting value 42 at index 4
0 1 2 3 42 4 5 6 7 8 9
```

Performance scenario:
- considered positions: beginning, middle, end
- perform fixed number of runs for each position, summ up total times (to avoid OS related delays)
  
Source: insert_element_perf.c
```c
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100


void arrayInsert(int* array, int value, int position)
{
    // Start clock
    clock_t t = clock();    
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
    {
        // Insert element - move affected elements one position right
        for(int j = ARR_SIZE - 1; j > position; j--) 
        {
            array[j] = array[j - 1];
        }
        // Insert a new value
        array[position] = value;
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t)/CLOCKS_PER_SEC;
    printf("Experiment: %d is inserted to index %d. Time of %d runs = %f seconds \n", value, position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main()
{
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
    
    // Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++)
    {
        array[i] = rand();
    }    
    
    // Make 3 insertions - 0, middle and last positions
    int insertNumber = 42;    
    arrayInsert(array, insertNumber, 0);
    arrayInsert(array, insertNumber, ARR_SIZE / 2);
    arrayInsert(array, insertNumber, ARR_SIZE - 1);
    
}
```

Output: insert_element_perf.c
```bash
Experiment: 42 is inserted to index 0. Time of 100 runs = 0.078000 seconds
Experiment: 42 is inserted to index 250000. Time of 100 runs = 0.032000 seconds
Experiment: 42 is inserted to index 499999. Time of 100 runs = 0.000000 seconds
```

### Section 3: Array: delete an element + measure the performance
Source: delete_element_alg.c

```c
#include <stdio.h>

#define ARR_SIZE 10


// Function to print an array - it accepts pointer to the array's memory and array's size
void printArray(int* arr, int len)
{
    for(int i = 0; i < len; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");    
}

int main()
{
    // Initialize an array and variables
    int array[ARR_SIZE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};    
    int deleteIndex = 4;
    int arrayActualLen = ARR_SIZE;
    
    // Print the initial array 
    printf("Initial array:\n");    
    printArray(array, ARR_SIZE);    
    
    // Delete element - move affected elements one position left
    for(int i = deleteIndex + 1; i < ARR_SIZE; i++)
    {
        array[i - 1] = array[i];
    }
    
    // Change the array's actual length
    arrayActualLen--;  
    
    // Print the resulting array
    printf("New array size = %d \n", arrayActualLen);
    printf("Array after deleting value at index %d \n", deleteIndex);
    printArray(array, arrayActualLen);

    return 0;
}
```

Output: delete_element_alg.c
```bash
Initial array:
0 1 2 3 4 5 6 7 8 9
New array size = 9
Array after deleting value at index 4
0 1 2 3 5 6 7 8 9
```

Performance scenario:
- considered positions: beginning, middle, end
- perform fixed number of runs for each position, summ up total times (to avoid OS related delays)
  
Source: delete_element_perf.c
```c
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100


void arrayDelete(int* array, int position)
{
    // Start clock
    clock_t t = clock();    
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
    {
        // Delete element - move affected elements one position left
        for(int i = position + 1; i < ARR_SIZE; i++)
        {
            array[i - 1] = array[i];
        }       
        // Here we do not need to make a variable for actual lenghtChange
        // since it is not used here, we need only the time
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t)/CLOCKS_PER_SEC;
    printf("Experiment: Value at index %d is deleted. Time of %d runs = %f seconds \n", position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main()
{
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
    
    // Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++) 
    {
        array[i] = rand();
    }    
            
    // Make 3 deletions - 0, middle and last positions    
    arrayDelete(array, 0);
    arrayDelete(array, ARR_SIZE / 2);
    arrayDelete(array, ARR_SIZE - 1);
    

    return 0;
}
```

Output: delete_element_perf.c
```bash
Experiment: Value at index 0 is deleted. Time of 100 runs = 0.109000 seconds
Experiment: Value at index 250000 is deleted. Time of 100 runs = 0.047000 seconds
Experiment: Value at index 499999 is deleted. Time of 100 runs = 0.000000 seconds
```
### Section 4: Array: find an element + measure the performance
Source: find_element_index_alg.c

```c
#include <stdio.h>

#define ARR_SIZE 10

// Function to print an array - it accepts pointer to the array's memory and array's size
void printArray(int* arr, int len)
{
    for(int i = 0; i < len; i++)
	{
        printf("%d ", arr[i]);
    }
	printf("\n");	
}

int main() 
{
	
	// Initialize an array and variables
    int array[ARR_SIZE] = {0, 11, 2, 33, 24, 5, 16, 37, 85, 99};	   
	// Target to find
    char elementToFind = 16;
	// Variable for resulting index, initialize it to some bad value to check if it is changed finally
    int indexFound = -1;
		
	// Print the initial array 
	printf("Initial array:\n");	
	printArray(array, ARR_SIZE);    
    
    // For loop to find the target value
    for(int i = 0; i < ARR_SIZE; i++) 
	{
		// If target is found - save index and leave
        if(array[i] == elementToFind) 
		{
            indexFound = i;
			break;
        }
    }
	
	// If this variable is not changed - element is     
	if (indexFound != -1)
        printf("Element %d is found at index %d \n", elementToFind, indexFound);
	else
		printf("Element %d is not found\n", elementToFind, indexFound);

    return 0;
}
```

Output: find_element_index_alg.c
```bash
Initial array:
0 11 2 33 24 5 16 37 85 99
Element 16 is found at index 6
```

Performance scenario:
- considered positions: beginning, middle, end
- perform fixed number of runs for each position, summ up total times (to avoid OS related delays)
  
Source: find_element_index_perf.c
```c
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100

void findElement(int* array, int target)
{
    // Start clock
    clock_t t = clock();       
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
    {
        // Actually this variable is used only to "save" answer        
        int indexFound = -1; 
        // For loop to find the target value
        for(int i = 0; i < ARR_SIZE; i++) 
        {
             // If target is found - save index and leave
             if(array[i] == target) 
             {
                 indexFound = i;
                 break;
             }
        }
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t)/CLOCKS_PER_SEC;
    printf("Experiment: Element %d search . Time of %d runs = %f seconds \n", target, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main() 
{
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
    
    // Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++) 
    {
        array[i] = rand();
    }    
    
    // Make 3 search requsts - first element array[0], middle element and last element    
    findElement(array, array[0]);
    findElement(array, array[ARR_SIZE / 2]);
    findElement(array, array[ARR_SIZE - 1]);
        
    return 0;
}
```

Output: find_element_index_perf.c
```bash
Experiment: Element 667933893 search . Time of 100 runs = 0.000000 seconds
Experiment: Element 2039841857 search . Time of 100 runs = 0.046000 seconds
Experiment: Element 537035320 search . Time of 100 runs = 0.094000 seconds
```
### Section 5: Array: get an element by index + measure the performance
Source: get_element_by_index_perf.c
Performance scenario:
- considered positions: beginning, middle, end
- perform fixed number of runs for each position, summ up total times (to avoid OS related delays)

```c
#include <stdint.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>

#define ARR_SIZE 500000
#define NUM_ITERATIONS_PER_EXPERIMENT 100


void getElement(int* array, int position)
{
    // Start clock
    clock_t t = clock();    
    // Make NUM_ITERATIONS_PER_EXPERIMENT runs to avoid some OS related delays
    for(int i = 0; i < NUM_ITERATIONS_PER_EXPERIMENT; i++)
    {
        // Variable where we read the data from the array        
        int elementValue = 0;
        // Read element at the position        
        // Actually this variable it is not used
        // we need it only to read the value and compute total time
        elementValue = array[position];              
    }
    // Finish clock, compute total time spent in seconds
    t = clock() - t;
    double timeSpent = ((double)t)/CLOCKS_PER_SEC;
    printf("Experiment: Read value at index %d. Time of %d runs = %f seconds \n", position, NUM_ITERATIONS_PER_EXPERIMENT, timeSpent);   
}

int main() 
{
    // Variables declaration
    int array[ARR_SIZE];

    // Initialize random seed
    srand(999);
    
    // Fill an array with initial uniformly distributed random values (last position is "free")
    for(int i = 0; i < ARR_SIZE - 1; i++) 
    {
        array[i] = rand();
    }    
    
    // Make 3 reads - 0, middle and last positions    
    getElement(array, 0);
    getElement(array, ARR_SIZE / 2);
    getElement(array, ARR_SIZE - 1);
        
    return 0;
}

```

Output: get_element_by_index_perf.c
```bash
Experiment: Read value at index 0. Time of 100 runs = 0.000000 seconds
Experiment: Read value at index 250000. Time of 100 runs = 0.000000 seconds
Experiment: Read value at index 499999. Time of 100 runs = 0.000000 seconds
```
