#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct adjacency_list_line {
    size_t* adjacencies;
    size_t adjacency_number;
} adjacency_list_line_t;

typedef struct adjacency_list {
    adjacency_list_line_t** lines;
    size_t n_vertices;
} adjacency_list_t;

void new_adjacency_list(adjacency_list_t* list, size_t n_vertices) {
    list->n_vertices = n_vertices;
    list->lines = (adjacency_list_line_t**)malloc(sizeof(adjacency_list_line_t*) * list->n_vertices);

    for (size_t i = 0; i < list->n_vertices; i++) {
        list->lines[i] = (adjacency_list_line_t*)malloc(sizeof(adjacency_list_line_t));

        // created with static size for now
        // can be created with smaller size and dynamically resized for memory consuprion reduction
        list->lines[i]->adjacencies = malloc(sizeof(size_t) * list->n_vertices);
        list->lines[i]->adjacency_number = 0;
    }

}

void delete_adjacency_list(adjacency_list_t* list) {
    for (size_t i = 0; i < list->n_vertices; i++) {
        free(list->lines[i]->adjacencies);
        free(list->lines[i]);
    }

    free(list->lines);
}

int add_edge(adjacency_list_t* list, size_t from, size_t to) {
    if(from >= list->n_vertices || to >= list->n_vertices) {
        return 1;
    }

    adjacency_list_line_t* line = list->lines[from];

    line->adjacencies[line->adjacency_number] = to;
    line->adjacency_number++;
    return 0;
}

void print_adjacency_list(adjacency_list_t* list) {
    for (size_t i = 0; i < list->n_vertices; i++) {
        printf("%ld: ", i);

        for (size_t j = 0; j < list->lines[i]->adjacency_number; j++) {
            printf("%ld ", list->lines[i]->adjacencies[j]);
        }

        printf("\n");
    }

    printf("\n");
}

int main() {

    adjacency_list_t l;
    adjacency_list_t* p_l = &l;

    new_adjacency_list(p_l, 8);

    print_adjacency_list(p_l);

    add_edge(p_l, 2, 3);
    add_edge(p_l, 3, 5);

    add_edge(p_l, 2, 6);
    add_edge(p_l, 6, 7);
    add_edge(p_l, 7, 5);

    print_adjacency_list(p_l);

    delete_adjacency_list(p_l);

    return 0;
}
