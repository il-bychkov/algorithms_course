#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100
#define N_ITERATIONS 1000
void swap(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(int* heap, int size, int i)
{
    if (!heap) {
        printf("Invalid Heap!\n");
        return;
    }
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    int biggest = i;
    if (leftChild < size
        && heap[leftChild] > heap[biggest]) {
        biggest = leftChild;
    }
    if (rightChild < size
        && heap[rightChild] > heap[biggest]) {
        biggest = rightChild;
    }

    if (biggest != i) {
        swap(heap + i, heap + biggest);
        heapify(heap, size, biggest);
    }
}

// building heap form the whole array
void buildHeap(int* arr, int size)
{
    int start = size / 2 - 1;
    for (int i = start; i >= 0; i--) {
        heapify(arr, size, i);
    }
}

// add_node new element
void add_node(int* heap, int* size, int element)
{
    if (*size == MAX_SIZE) {
        printf("Heap Overflow!\n");
        return;
    }

    heap[*size] = element;
    (*size)++;

    int i = *size - 1;
    while (i > 0) {
        if (heap[(i - 1) / 2] < heap[i]) {
            swap(heap + (i - 1) / 2, heap + i);
            i = (i - 1) / 2;
        }

        else {
            break;
        }
    }
}

// delete elements
void delete(int* heap, int* size, int index)
{
    if (size == 0) {
        printf("Heap Underflow\n");
        return;
    }

    heap[index] = heap[*size - 1];
    *size = *size - 1;

    heapify(heap, *size, index);
}

// extract the maximum
int get_max(int* heap, int* size)
{
    int max = heap[0];

    delete (heap, size, 0);

    return max;
}

int main()
{
    int heap[MAX_SIZE];
    int size = 0;

    add_node(heap, &size, 1);
    add_node(heap, &size, 2);
    add_node(heap, &size, 3);
    add_node(heap, &size, 44);
    add_node(heap, &size, 5);
    add_node(heap, &size, 100);
    add_node(heap, &size, 7);
    add_node(heap, &size, 88);
    add_node(heap, &size, 9);
    add_node(heap, &size, 10);

    while (size != 0) {
        printf("%d\n", get_max(heap, &size));
    }


    clock_t t;
    double time_taken = 0;

    for (int n_exp = 0; n_exp < N_ITERATIONS; n_exp++) {

        size = 0;

        t = clock();

        add_node(heap, &size, 1);
        add_node(heap, &size, 2);
        add_node(heap, &size, 3);
        add_node(heap, &size, 44);
        add_node(heap, &size, 5);
        add_node(heap, &size, 100);
        add_node(heap, &size, 7);
        add_node(heap, &size, 88);
        add_node(heap, &size, 9);
        add_node(heap, &size, 10);

        t = clock() - t;

        time_taken += ((double)t) / CLOCKS_PER_SEC;
    }

    printf("%d heap creations executed in %f seconds \n", N_ITERATIONS, time_taken);

    return 0;
}
