#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// data structures
typedef struct linked_list_node {
    uint32_t value;
    struct linked_list_node* next;
    struct linked_list_node* prev;
} linked_list_node_t;

typedef struct queue {
    struct linked_list_node* head;
    struct linked_list_node* tail;
} queue_t;

void new(queue_t* queue) {
    queue->head = NULL;
    queue->tail = NULL;
};

void delete(queue_t* queue) {
    linked_list_node_t* tail = queue->head;

    while (tail) {
        linked_list_node_t* current = tail;
        tail = tail->next;
        free(current);
    }
};

void enqueue(queue_t* queue, uint32_t value) {
    linked_list_node_t* head = queue->head;

    queue->head = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

    if (queue->tail == NULL)
    {
        queue->tail = queue->head;
    }

    if (head != NULL) {
        head->prev = queue->head;
    }

    queue->head->next = head;
    queue->head->prev = NULL;
    queue->head->value = value;
}

bool isEmpty(queue_t* queue) {
    return queue->head == NULL;
}

uint32_t dequeue(queue_t* queue) {

    uint32_t value = 0;

    if(!isEmpty(queue)) {
        value = queue->tail->value;

        linked_list_node_t* new_tail = queue->tail->prev;

        if(new_tail) {
            new_tail->next == NULL;
        }

        if(queue->tail == queue->head) {
            queue->head = new_tail;
        }

        queue->tail = new_tail;
    }

    return value;
}

int main() {
    queue_t queue;
    queue_t* p_queue = &queue;

    new(p_queue);

    uint32_t val_1 = 1;
    uint32_t val_2 = 22;
    uint32_t val_3 = 333;
    uint32_t val_4 = 4444;

    uint32_t out_val;

    enqueue(p_queue, val_1);
    printf("enqueue %d\n", val_1);
    enqueue(p_queue, val_2);
    printf("enqueue %d\n", val_2);

    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);

    enqueue(p_queue, val_3);
    printf("enqueue %d\n", val_3);
    enqueue(p_queue, val_4);
    printf("enqueue %d\n", val_4);

    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);
    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);
    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);

    delete(p_queue);

    return 0;
}
