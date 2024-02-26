#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef struct edje {
    size_t from;
    size_t to;
} edje_t;

typedef struct edjes_list {
    edje_t** list;
    size_t list_len;
    size_t n_edjes;
} edjes_list_t;

void new_edjes_list(edjes_list_t* list) {
    list->list_len = 8;
    list->list = malloc(sizeof(edje_t*) * list->list_len);
    list->n_edjes = 0;
}

void delete_edjes_list(edjes_list_t* list) {
    for (size_t i = 0; i < list->n_edjes; i++) {
        free(list->list[i]);
    }

    free(list->list);
}

void add_edge(edjes_list_t* list, size_t from, size_t to) {

    // resize if needed
    if (list->n_edjes+1 == list->list_len)
    {
        list->list_len *= 2;
        edje_t** new_list = malloc(sizeof(edje_t*) * list->list_len);
        memcpy(new_list, list->list, list->n_edjes);
        free(list->list);
        list->list = new_list;
    }

    list->list[list->n_edjes] = malloc(sizeof(edje_t));
    list->list[list->n_edjes]->from = from;
    list->list[list->n_edjes]->to = to;

    list->n_edjes++;
}

void print_edjes_list(edjes_list_t* list) {
    for (size_t i = 0; i < list->n_edjes; i++) {
        printf("%ld to %ld ", list->list[i]->from, list->list[i]->to);
        printf("\n");
    }
}

int main() {

    edjes_list_t l;
    edjes_list_t* p_l = &l;

    new_edjes_list(p_l);

    print_edjes_list(p_l);

    add_edge(p_l, 2, 3);
    add_edge(p_l, 3, 5);

    add_edge(p_l, 2, 6);
    add_edge(p_l, 6, 7);
    add_edge(p_l, 7, 5);

    print_edjes_list(p_l);

    delete_edjes_list(p_l);

    return 0;
}
