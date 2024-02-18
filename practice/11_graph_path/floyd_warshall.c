#include "graph.h"

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
