#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


typedef struct queue {
    uint32_t* buffer;
    size_t max_size;
    size_t el_count;
    size_t head;
    size_t tail;
} queue_t;

void new(queue_t* queue, size_t max_size) {
    queue->buffer = (uint32_t*)malloc(max_size * sizeof(uint32_t));
    queue->max_size = max_size;
    queue->el_count = 0;
    queue->head = 0;
    queue->tail= 0;
};

void delete(queue_t* queue) {
    free(queue->buffer);
};

bool isEmpty(queue_t* queue) {
    return queue->el_count == 0;
}

bool isFull(queue_t* queue) {
    return queue->el_count == queue->max_size;
}

void enqueue(queue_t* queue, uint32_t value) {
    if(!isFull(queue)) {
        queue->buffer[queue->head] = value;
        queue->head = (queue->head + 1) % queue->max_size;
        queue->el_count++;
    }
}

uint32_t dequeue(queue_t* queue) {

    uint32_t value = 0;

    if(!isEmpty(queue)) {
        value = queue->buffer[queue->tail];

        queue->tail = (queue->tail + 1) % queue->max_size;
        queue->el_count--;
    }

    return value;
}

int main() {
    queue_t queue;
    queue_t* p_queue = &queue;

    new(p_queue, 5);

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
    printf("\n");
    printf("dequeue %d\n", out_val);
    printf("\n");

    enqueue(p_queue, val_3);
    printf("enqueue %d\n", val_3);
    enqueue(p_queue, val_4);
    printf("enqueue %d\n", val_4);

    printf("\n");

    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);
    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);
    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);

    printf("\n");

    enqueue(p_queue, val_1);
    printf("enqueue %d\n", val_1);
    enqueue(p_queue, val_2);
    printf("enqueue %d\n", val_2);

    out_val = dequeue(p_queue);
    printf("\n");
    printf("dequeue %d\n", out_val);
    printf("\n");

    enqueue(p_queue, val_3);
    printf("enqueue %d\n", val_3);
    enqueue(p_queue, val_4);
    printf("enqueue %d\n", val_4);

    printf("\n");
    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);
    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);
    out_val = dequeue(p_queue);
    printf("dequeue %d\n", out_val);

    delete(p_queue);

    return 0;
}
