#include "graph.h"

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
