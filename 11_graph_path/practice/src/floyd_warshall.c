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

// implementation based on:
// https://ru.wikipedia.org/wiki/Алгоритм_Флойда_—_Уоршелла
// tested on data from:
// https://habr.com/ru/companies/otus/articles/484382/

typedef struct floyd_warshall_context {
    size_t* next;
    int8_t* distanse;
    size_t n_vertices;
} floyd_warshall_context_t;

void new_floyd_warshall_context(floyd_warshall_context_t* context, size_t n_vertices) {
    context->next = malloc(sizeof(size_t) * n_vertices * n_vertices);
    context->distanse = malloc(sizeof(int8_t) * n_vertices * n_vertices);

    context->n_vertices = n_vertices;
};

void delete_floyd_warshall_context(floyd_warshall_context_t* context) {
    free(context->distanse);
    free(context->next);
};

void print_pathes(floyd_warshall_context_t* context, size_t from) {
    printf("\npath start         : %ld\n", from);
    printf("number of vertices : %ld\n\n", context->n_vertices);

    for (size_t i = 0; i < context->n_vertices; i++)
    {
        printf("path from %ld to %ld : ", from, i);

        if(context->distanse[context->n_vertices * from + i] < INT8_MAX) {
            printf("length %d\n", context->distanse[context->n_vertices * from + i]);

            size_t current = from;

            while (current != i) {
                printf("%ld -> ", current);
                current = context->next[context->n_vertices * current + i];
            }

            printf("%ld\n", current);
        } else {
            printf("no path\n");
        }
    }
}

void floyd_warshall(graph_t* graph, floyd_warshall_context_t* context) {

    size_t n_vertices = graph->n_vertices;

    size_t* next = context->next;
    int8_t* distance = context->distanse;

    // initialization
    for (size_t i = 0; i < n_vertices; i++) {
        for (size_t j = 0; j < n_vertices; j++) {
            distance[n_vertices * i + j] = get_distance(graph, i, j);
            next[n_vertices * i + j] = j;
        }
    }

    for (size_t i = 0; i < n_vertices; i++) {
        distance[n_vertices * i + i] = 0;
        next[n_vertices * i + i] = i;
    }

    // algoritm itself
    for (size_t k = 0; k < n_vertices; k++) {
        for (size_t i = 0; i < n_vertices; i++) {
            for (size_t j = 0; j < n_vertices; j++) {
                if (is_ajacend(graph, i, k) || is_ajacend(graph, k, j)) {
                    if (distance[n_vertices * i + j] > distance[n_vertices * i + k] + distance[n_vertices * k + j]) {
                        distance[n_vertices * i + j] = distance[n_vertices * i + k] + distance[n_vertices * k + j];
                        next[n_vertices * i + j] = next[n_vertices * i + k];
                    }

                }

            }

        }

    }

}

int main() {

    graph_t g;
    graph_t* p_g = &g;

    floyd_warshall_context_t ctx;
    floyd_warshall_context_t* p_ctx = &ctx;

    new_graph(p_g, 5, ordered);
    new_floyd_warshall_context(p_ctx, 5);

    add_edge(p_g, 0, 1, -1);
    add_edge(p_g, 0, 2, 4);
    add_edge(p_g, 1, 2, 2);
    add_edge(p_g, 1, 3, 2);
    add_edge(p_g, 1, 4, 2);
    add_edge(p_g, 3, 1, 1);
    add_edge(p_g, 3, 2, 5);
    add_edge(p_g, 4, 3, -3);

    floyd_warshall(p_g, p_ctx);

    print_graph(p_g);
    print_pathes(p_ctx, 0);
    print_pathes(p_ctx, 3);

    return 0;
}
