#include <stdio.h>
 
#define SIZE 350

// Based on the solution from Alex Larkov


// We will need to print array several times, so lets define a function 
void print(int* arr, int* size)
{
    for (int i = 0; i < *size; ++i)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}


// Function recieves array pointer, insertion index, value to insert and a pointer to array size (we will need to modify it)
void insert(int* arr, int index, int val, int* size)
{
    for (int i = *size - 1; i >= index; --i)
    {
        arr[i + 1] = arr[i];
    }    
    arr[index] = val;
    *size += 1;
}

// Function recieves array pointer, index to delete and a pointer to array size (we will need to modify it)
void delete(int* arr, int index, int* size)
{
    for (int i = index; i < *size - 1; ++i)
    {
        arr[i] = arr[i + 1];
    }    
    *size -= 1;
}
 
int main() 
{
    int n;
    int arr[SIZE] = {0};
    
    // Read input data
    scanf("%d", &n); 
    for (int i = 0; i < n; ++i) 
    {
        scanf("%d", &arr[i]);
    }
 
    int m;
    scanf("%d", &m);
    
    // Define variables to store input values from requests
    int t;
    int index, val;
    
    for (int i = 0; i < m; ++i) {
        
        scanf("%d", &t);
        if (t == 0) {    
            // If request == insert - call insertion function
            scanf("%d%d", &index, &val);
            --index;
            insert(arr, index, val, &n);
        } else {            
            // If request == delete - call deletion function
            scanf("%d", &index);
            --index;
            delete(arr, index, &n);
        }
        print(arr, &n);
    }
    return 0;
};