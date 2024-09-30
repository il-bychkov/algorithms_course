#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// data structures
typedef struct linked_list_node {
    uint32_t value;
    struct linked_list_node* next;
} linked_list_node_t;

typedef struct linked_list {
    struct linked_list_node* head;
} linked_list_t;

// private functions
linked_list_node_t* get_tail_node(linked_list_t* list) {
    linked_list_node_t* tail = list->head;

    while (tail && tail->next) {
        tail = tail->next;
    }

    return tail;
}

linked_list_node_t* get_node_by_value(linked_list_t* list, uint32_t value) {
    linked_list_node_t* tail = list->head;

    while (tail && tail->next) {
        if (tail->value == value) {
            return tail;
        }

        tail = tail->next;
    }

    return NULL;
}

linked_list_node_t* get_previous_node_by_value(linked_list_t* list, uint32_t value) {
    linked_list_node_t* tail = list->head;

    while (tail && tail->next) {
        if (tail->next->value == value) {
            return tail;
        }

        tail = tail->next;
    }

    return NULL;
}

// public functions
// constructor and distructor
void new(linked_list_t* list) {
    list->head = NULL;
};

void delete(linked_list_t* list) {
    linked_list_node_t* tail = list->head;

    while (tail) {
        linked_list_node_t* current = tail;
        tail = tail->next;
        free(current);
    }
};

// insertion functions
void insert_head(linked_list_t* list, uint32_t value) {
    linked_list_node_t * head = list->head;

    list->head = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

    list->head->next = head;
    list->head->value = value;
}

void insert_tail(linked_list_t* list, uint32_t value) {

    linked_list_node_t* tail = get_tail_node(list);

    tail->next = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

    tail->next->next = NULL;
    tail->next->value = value;
}

void insert_after_value(linked_list_t* list, uint32_t value_to_insert_after, uint32_t value) {
    linked_list_node_t* node_to_insert_after = get_node_by_value(list, value_to_insert_after);

    if(node_to_insert_after) {
        linked_list_node_t* inserted_node = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

        inserted_node->value = value;
        inserted_node->next = node_to_insert_after->next;
        node_to_insert_after->next = inserted_node;
    } else {
        insert_tail(list, value);
    }
}

void insert_before_value(linked_list_t* list, uint32_t value_to_insert_before, uint32_t value) {
    linked_list_node_t* node_to_insert_after = get_previous_node_by_value(list, value_to_insert_before);

    if(node_to_insert_after) {
        linked_list_node_t* inserted_node = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

        inserted_node->value = value;
        inserted_node->next = node_to_insert_after->next;
        node_to_insert_after->next = inserted_node;
    } else {
        insert_head(list, value);
    }
}

// deletion function
void delete_value(linked_list_t* list, uint32_t value_to_delete) {
    linked_list_node_t* node_to_delete_after = get_previous_node_by_value(list, value_to_delete);

    if(node_to_delete_after) {
        linked_list_node_t* next_node_after_deleted = node_to_delete_after->next->next;
        free(node_to_delete_after->next);
        node_to_delete_after->next = next_node_after_deleted;
    }
}

// printing
void print_list(linked_list_t* list) {
    linked_list_node_t* tail = list->head;

    while (tail) {
        printf("%d, ", tail->value);
        tail = tail->next;
    }

    printf("\n");
}

int main() {

    linked_list_t list;
    linked_list_t* p_list = &list;

    new(p_list);

    insert_head(p_list, 0);
    printf("insert 0 after initialization:\n");
    print_list(p_list);

    insert_head(p_list, 8);
    printf("insert 8 to head:\n");
    print_list(p_list);

    insert_tail(p_list, 12);
    printf("insert 12 to tail:\n");
    print_list(p_list);

    insert_after_value(p_list, 0, 42);
    printf("insert 42 after 0:\n");
    print_list(p_list);

    insert_before_value(p_list, 0, 67);
    printf("insert 67 before 0:\n");
    print_list(p_list);

    delete_value(p_list, 0);
    printf("delete 0:\n");
    print_list(p_list);

    delete(p_list);

    return 0;
}
