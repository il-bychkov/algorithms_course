#include <stdio.h>

#define SIZE 350
int n;

// Solution from Alex Larkov KNT9

void print(int arr[SIZE]) 
{
    for (int i = 0; i < n; ++i) 
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void insert(int arr[SIZE], int index, int val) 
{
    for (int i = n - 1; i >= index; --i) 
    {
        arr[i + 1] = arr[i];
    }
    ++n;
    arr[index] = val;
}

void delete(int arr[SIZE], int index) 
{
    for (int i = index; i < n - 1; ++i) 
    {
        arr[i] = arr[i + 1];
    }
    --n;
}

int main() 
{
    int arr[SIZE] = {0};
    scanf("%d", &n);

    for (int i = 0; i < n; ++i) 
    {
        scanf("%d", &arr[i]);
    }

    int m;
    scanf("%d", &m);

    for (int i = 0; i < m; ++i) 
    {
        int t;
        scanf("%d", &t);
        if (t == 0) 
        {
            int index, val;
            scanf("%d%d", &index, &val);
            --index;
            insert(arr, index, val);
        } else 
        {
            int index;
            scanf("%d", &index);
            --index;
            delete(arr, index);
        }
        print(arr);
    }
    return 0;
};