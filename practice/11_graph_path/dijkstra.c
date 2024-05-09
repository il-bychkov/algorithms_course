#include "graph.h"

// implementation based on:
// https://ru.wikipedia.org/wiki/Алгоритм_Дейкстры
// tested on data from:
// https://ru.wikipedia.org/wiki/Алгоритм_Дейкстры

void dijkstra(graph_t* graph, path_set_t* path_set, size_t start) {

    path_set->path_start = start;

    size_t n_vertices = graph->n_vertices;

    size_t* previous = path_set->previous;
    int8_t* distance = path_set->distanse;
    bool* visited = malloc(sizeof(bool) * n_vertices);

    for (size_t i = 0; i < n_vertices; i++) {
        distance[i] = INT8_MAX;
        previous[i] = i;
        visited[i] = false;
    }

    distance[start] = 0;
    size_t current = start;

    bool is_exist_unvisited = true;

    while (is_exist_unvisited) {
        size_t min_ajacent = current;
        int8_t min_distance = INT8_MAX;

        is_exist_unvisited = false;
        visited[current] = true;

        for (size_t i = 0; i < n_vertices; i++) {
            if (is_ajacend(graph, current, i) && !visited[i]) {
                is_exist_unvisited = true;

                int8_t distance_to_ajacent = get_distance(graph, current, i) + distance[current];

                if(distance_to_ajacent < distance[i]) {
                    distance[i] = distance_to_ajacent;
                    previous[i] = current;
                }

                if(distance_to_ajacent < min_distance) {
                    min_distance = distance_to_ajacent;
                    min_ajacent = i;
                }
            }

        }
        current = min_ajacent;
    }
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

    dijkstra(p_g, p_p, 0);

    printf("\nFind pathes in unordered graph without negative edjes:\n");
    print_graph(p_g);
    print_path_set(p_p);

    return 0;
}
