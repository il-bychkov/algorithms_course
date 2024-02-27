#ifndef GRAPH_H
#define GRAPH_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum graph_order {
    ordered,
    unordered
} graph_order_r;

typedef struct graph {
    int8_t* matrix;
    size_t n_vertices;
    graph_order_r order;
} graph_t;

void new_graph(graph_t* graph, size_t n_vertices, graph_order_r order);
void delete_graph(graph_t* graph);

int add_edge(graph_t* graph, size_t from, size_t to, int8_t weight);
bool is_ajacend(graph_t* graph, size_t from, size_t to);
int8_t get_distance(graph_t* graph, size_t from, size_t to);
void print_graph(graph_t* graph);

typedef struct path_set {
    size_t* previous;
    int8_t* distanse;
    size_t n_vertices;
    size_t path_start;
} path_set_t;

void new_path_set(path_set_t* path_set, size_t n_vertices);
void delete_path_set(path_set_t* path_set);
void print_path_set(path_set_t* path_set);

#endif // GRAPH_H
