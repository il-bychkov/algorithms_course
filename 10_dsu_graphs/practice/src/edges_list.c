#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct edge {
    size_t from;
    size_t to;
} edge_t;

typedef struct edges_list {
    edge_t** list;
    size_t list_len;
    size_t n_edges;
} edges_list_t;

void new_edges_list(edges_list_t* list) {
    list->list_len = 8;
    list->list = malloc(sizeof(edge_t*) * list->list_len);
    list->n_edges = 0;
}

void delete_edges_list(edges_list_t* list) {
    for (size_t i = 0; i < list->n_edges; i++) {
        free(list->list[i]);
    }

    free(list->list);
}

void add_edge(edges_list_t* list, size_t from, size_t to) {

    // resize if needed
    if (list->n_edges+1 == list->list_len)
    {
        list->list_len *= 2;
        edge_t** new_list = malloc(sizeof(edge_t*) * list->list_len);
        memcpy(new_list, list->list, list->n_edges);
        free(list->list);
        list->list = new_list;
    }

    list->list[list->n_edges] = malloc(sizeof(edge_t));
    list->list[list->n_edges]->from = from;
    list->list[list->n_edges]->to = to;

    list->n_edges++;
}

void print_edges_list(edges_list_t* list) {
    for (size_t i = 0; i < list->n_edges; i++) {
        printf("%ld to %ld ", list->list[i]->from, list->list[i]->to);
        printf("\n");
    }
}

int main() {

    edges_list_t l;
    edges_list_t* p_l = &l;

    new_edges_list(p_l);

    print_edges_list(p_l);

    add_edge(p_l, 2, 3);
    add_edge(p_l, 3, 5);

    add_edge(p_l, 2, 6);
    add_edge(p_l, 6, 7);
    add_edge(p_l, 7, 5);

    print_edges_list(p_l);

    delete_edges_list(p_l);

    return 0;
}
