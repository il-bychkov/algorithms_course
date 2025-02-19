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

typedef struct path_set {
    size_t* previous;
    int8_t* distanse;
    size_t n_vertices;
    size_t path_start;
} path_set_t;

void new_graph(graph_t* graph, size_t n_vertices, graph_order_r order) {
    graph->order = order;
    graph->n_vertices = n_vertices;
    graph->matrix = malloc(sizeof(int8_t) * n_vertices * n_vertices);

    for (size_t i = 0; i < n_vertices * n_vertices; i++) {
        graph->matrix[i] = INT8_MAX;
    }
};

void delete_graph(graph_t* graph) {
    free(graph->matrix);
};

int add_edge(graph_t* graph, size_t from, size_t to, int8_t weight) {
    if(from >= graph->n_vertices || to >= graph->n_vertices) {
        return 1;
    }
    graph->matrix[graph->n_vertices * from + to] = weight;
    if (graph->order == unordered) {
        graph->matrix[graph->n_vertices * to + from] = weight;
    }

    return 0;
};

bool is_ajacend(graph_t* graph, size_t from, size_t to) {
    return graph->matrix[graph->n_vertices * from + to] != INT8_MAX;
};

int8_t get_distance(graph_t* graph, size_t from, size_t to) {
    return graph->matrix[graph->n_vertices * from + to];
};

// works well with graphs with <10 vertices only
void print_graph(graph_t* graph) {
    printf("   │");
    for (size_t i = 0; i < graph->n_vertices; i++) {
        printf(" %4ld", i);
    }

    printf("\n");

    printf("───┼");
    for (size_t i = 0; i < graph->n_vertices; i++) {
        printf("─────");
    }

    printf("\n");

    for (size_t i = 0; i < graph->n_vertices; i++) {
        printf(" %ld │", i);

        for (size_t j = 0; j < graph->n_vertices; j++) {

            if (is_ajacend(graph, i, j)) {
                printf(" %4d", get_distance(graph, i, j));
            } else {
                printf("     ");
            }
        }

        printf("\n");
    }

    printf("\n");
};

void new_path_set(path_set_t* path_set, size_t n_vertices) {
    path_set->previous = malloc(sizeof(size_t) * n_vertices);
    path_set->distanse = malloc(sizeof(int8_t) * n_vertices);

    path_set->n_vertices = n_vertices;
};

void delete_path_set(path_set_t* path_set) {
    free(path_set->distanse);
    free(path_set->previous);
};

void print_path_set(path_set_t* path_set) {
    printf("\npath start         : %ld\n", path_set->path_start);
    printf("number of vertices : %ld\n\n", path_set->n_vertices);

    size_t* path_buffer = malloc(sizeof(size_t) * path_set->n_vertices);
    size_t path_buffer_len = path_set->n_vertices;

    for (size_t i = 0; i < path_set->n_vertices; i++)
    {
        printf("path from %ld to %ld : ", path_set->path_start, i);
        path_buffer_len = path_set->n_vertices - 1;

        if(path_set->distanse[i] < INT8_MAX) {
            printf("length %d\n", path_set->distanse[i]);

            size_t current = i;

            path_buffer[path_buffer_len] = current;
            path_buffer_len--;

            while (path_set->previous[current] != current) {
                path_buffer[path_buffer_len] = current;
                path_buffer_len--;
                current = path_set->previous[current];
            }

            path_buffer[path_buffer_len] = current;
            path_buffer_len--;

            for (size_t i = path_buffer_len + 1; i < path_set->n_vertices - 2; i++) {
                printf("%ld -> ", path_buffer[i]);
            }

            printf("%ld\n", path_buffer[path_set->n_vertices - 1]);

        } else {
            printf("no path\n");
        }
    }

    free(path_buffer);

    return;
};

bool bellman_ford(graph_t* graph, path_set_t* path_set, size_t start) {

    path_set->path_start = start;

    size_t n_vertices = graph->n_vertices;

    size_t* previous = path_set->previous;
    int8_t* distance = path_set->distanse;

    for (size_t i = 0; i < n_vertices; i++) {
        distance[i] = INT8_MAX;
        previous[i] = i;
    }

    distance[start] = 0;

    // find pathes
    for (size_t bf_iterations = 0; bf_iterations < n_vertices - 1; bf_iterations++) {
        for (size_t i = 0; i < n_vertices; i++) {
            for (size_t j = 0; j < n_vertices; j++) {
                if((distance[i] != INT8_MAX) && is_ajacend(graph, i, j)) {
                    int8_t new_distance = distance[i] + get_distance(graph, i, j);
                    if(new_distance < distance[j]) {
                        distance[j] = new_distance;
                        previous[j] = i;
                    }
                }
            }
        }
    }

    // check negative cycles
    for (size_t i = 0; i < n_vertices; i++) {
        for (size_t j = 0; j < n_vertices; j++) {
            if(distance[i] != INT8_MAX && is_ajacend(graph, i, j)) {
                int8_t new_distance = distance[i] + get_distance(graph, i, j);

                if(new_distance < distance[j]) {
                    return false;
                }
            }
        }
    }

    return true;
}

int main() {

    graph_t g;
    graph_t* p_g = &g;

    path_set_t p;
    path_set_t* p_p = &p;

    new_graph(p_g, 7, unordered);

    add_edge(p_g, 0, 1, 7);
    add_edge(p_g, 0, 2, 9);
    add_edge(p_g, 0, 5, 14);
    add_edge(p_g, 1, 2, 10);
    add_edge(p_g, 1, 3, 15);
    add_edge(p_g, 2, 3, 11);
    add_edge(p_g, 2, 5, 2);
    add_edge(p_g, 3, 4, 6);
    add_edge(p_g, 4, 5, 9);

    new_path_set(p_p, 7);

    bellman_ford(p_g, p_p, 0);

    printf("\nFind pathes in unordered graph without negative edjes:\n");
    print_graph(p_g);
    print_path_set(p_p);


    delete_graph(p_g);
    delete_path_set(p_p);

    new_graph(p_g, 5, ordered);

    add_edge(p_g, 0, 1, -1);
    add_edge(p_g, 0, 2, 4);
    add_edge(p_g, 1, 2, 2);
    add_edge(p_g, 1, 3, 2);
    add_edge(p_g, 1, 4, 2);
    add_edge(p_g, 3, 1, 1);
    add_edge(p_g, 3, 2, 5);
    add_edge(p_g, 4, 3, -3);

    new_path_set(p_p, 5);

    bellman_ford(p_g, p_p, 0);

    printf("\nFind pathes in ordered graph with negative edjes and without negative cycles:\n");
    print_graph(p_g);
    print_path_set(p_p);

    delete_path_set(p_p);
    new_path_set(p_p, 5);

    delete_path_set(p_p);
    new_path_set(p_p, 5);

    bellman_ford(p_g, p_p, 3);
    print_path_set(p_p);

    // will owerride edje
    add_edge(p_g, 1, 3, -2);

    bool is_no_negative_cycles = bellman_ford(p_g, p_p, 0);

    printf("\nCheck if can find negative cycles:\n");
    print_graph(p_g);
    if(is_no_negative_cycles) {
        printf("Negative cycle not found\n");
    } else {
        printf("Negative cycle found\n");
    }

    return 0;
}
