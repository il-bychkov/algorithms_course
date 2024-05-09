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

// find shortest path

typedef struct queue {
    size_t* buffer;
    size_t max_size;
    size_t el_count;
    size_t head;
    size_t tail;
} queue_t;

void new_q(queue_t* queue, size_t max_size) {
    queue->buffer = (size_t*)malloc(max_size * sizeof(size_t));
    queue->max_size = max_size;
    queue->el_count = 0;
    queue->head = 0;
    queue->tail= 0;
};

void delete_q(queue_t* queue) {
    free(queue->buffer);
};

bool isEmpty(queue_t* queue) {
    return queue->el_count == 0;
}

bool isFull(queue_t* queue) {
    return queue->el_count == queue->max_size;
}

void enqueue(queue_t* queue, size_t value) {
    if(!isFull(queue)) {
        queue->buffer[queue->head] = value;
        queue->head = (queue->head + 1) % queue->max_size;
        queue->el_count++;
    }
}

size_t dequeue(queue_t* queue) {

    size_t value = 0;

    if(!isEmpty(queue)) {
        value = queue->buffer[queue->tail];

        queue->tail = (queue->tail + 1) % queue->max_size;
        queue->el_count--;
    }

    return value;
}

bool find_shortest_path_by_bfs(adjacency_matrix_t* matrix, size_t* path, size_t* path_len, size_t from, size_t to) {

    bool* visited = malloc(sizeof(bool) * matrix->n_vertices);
    size_t* distanse = malloc(sizeof(size_t) * matrix->n_vertices);
    size_t* previous = malloc(sizeof(size_t) * matrix->n_vertices);

    for (size_t i = 0; i < matrix->n_vertices; i++) {
        visited[i] = false;
        distanse[i] = 0;
        previous[i] = i;
    }

    queue_t q;
    queue_t* p_q = &q;

    new_q(p_q, matrix->n_vertices);

    enqueue(p_q, from);

    while(!isEmpty(p_q)) {
        size_t current = dequeue(p_q);

        if(current == to) {

            *path_len = distanse[current];
            size_t index_to_fill = distanse[current];

            while (current != previous[current]) {
                path[index_to_fill] = current;
                index_to_fill--;
                current = previous[current];
            }

            path[index_to_fill] = current;

            delete_q(p_q);
            free(visited);
            free(distanse);
            free(previous);
            return true;
        }

        visited[current] = true;

        for (size_t i = 0; i < matrix->n_vertices; i++) {
            size_t child = current * matrix->n_vertices + i;
            if(matrix->matrix[child] && visited[i] == false) {
                enqueue(p_q, i);
                distanse[i] = distanse[current] + 1;
                previous[i] = current;
            }
        }
    }

    delete_q(p_q);
    free(visited);
    free(distanse);
    free(previous);
    return false;
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

    // shortest path

    size_t shortest_path[8];
    size_t shortest_path_len;
    bool is_found;

    is_found = find_shortest_path_by_bfs(p_m, shortest_path, &shortest_path_len, 2, 5);

    printf("\nsearch for shortest path from 2 to 5\n");

    if(is_found) {
        printf("found path of length %ld\npath is: \n", shortest_path_len);

        for (size_t i = 0; i < shortest_path_len; i++) {
            printf("%ld -> ", shortest_path[i]);
        }

        printf("%ld\n", shortest_path[shortest_path_len]);
    } else {
       printf("path not found\n");
    }

    is_found = find_shortest_path_by_bfs(p_m, shortest_path, &shortest_path_len, 0, 7);

    printf("\nsearch for shortest path from 0 to 7\n");

    if(is_found) {
        printf("found some path\n");
    } else {
       printf("path not found\n");
    }

    delete_adjacency_matrix(p_m);

    return 0;
}
