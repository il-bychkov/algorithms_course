#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct adjacency_matrix {
    bool* matrix;
    size_t n_vertices;
} adjacency_matrix_t;

void new_adjacency_matrix(adjacency_matrix_t* matrix, size_t n_vertices) {
   matrix->n_vertices = n_vertices;
   matrix->matrix = malloc(sizeof(bool) * n_vertices * n_vertices);

   for (size_t i = 0; i < n_vertices * n_vertices; i++)
   {
        matrix->matrix[i] = false;
   }

}

void delete_adjacency_matrix(adjacency_matrix_t* matrix) {
    free(matrix->matrix);
}

int add_edge(adjacency_matrix_t* matrix, size_t from, size_t to) {
    if(from >= matrix->n_vertices || to >= matrix->n_vertices) {
        return 1;
    }
    matrix->matrix[matrix->n_vertices * from + to] = true;
    return 0;
}

// works well with graphs with <10 vertices only
void print_adjacency_matrix(adjacency_matrix_t* matrix) {
    printf("   │");
    for (size_t i = 0; i < matrix->n_vertices; i++) {
        printf(" %ld", i);
    }

    printf("\n");

    printf("───┼");
    for (size_t i = 0; i < matrix->n_vertices; i++) {
        printf("──");
    }

    printf("\n");

    for (size_t i = 0; i < matrix->n_vertices; i++) {
        printf(" %ld │", i);

        for (size_t j = 0; j < matrix->n_vertices; j++) {
            if(matrix->matrix[matrix->n_vertices * i + j] == true) {
               printf(" X");
            } else {
                printf(" O");
            }
        }

        printf("\n");
    }

    printf("\n");
}

int main() {

    adjacency_matrix_t m;
    adjacency_matrix_t* p_m = &m;

    new_adjacency_matrix(p_m, 8);

    print_adjacency_matrix(p_m);

    add_edge(p_m, 2, 3);
    add_edge(p_m, 3, 5);

    add_edge(p_m, 2, 6);
    add_edge(p_m, 6, 7);
    add_edge(p_m, 7, 5);

    print_adjacency_matrix(p_m);

    delete_adjacency_matrix(p_m);

    return 0;
}
