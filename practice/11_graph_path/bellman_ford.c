#include "graph.h"

// implementation based on
// https://habr.com/ru/companies/otus/articles/484382/
// tested on data from:
// https://habr.com/ru/companies/otus/articles/484382/
// https://ru.wikipedia.org/wiki/Алгоритм_Дейкстры

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
