#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// data structures
typedef struct linked_list_node {
    uint32_t value;
    struct linked_list_node* next;
} linked_list_node_t;

typedef struct stack {
    struct linked_list_node* head;
    uint32_t max;
} stack_t;

// public functions
void new(stack_t* stack) {
    stack->head = NULL;
}

void delete(stack_t* stack) {
    linked_list_node_t* tail = stack->head;

    while (tail) {
        linked_list_node_t* current = tail;
        tail = tail->next;
        free(current);
    }
}

bool is_empty(stack_t* stack) {
    return stack->head == NULL;
}

void push(stack_t* stack, uint32_t value) {

    bool is_stack_empty = is_empty(stack);

    linked_list_node_t * head = stack->head;

    stack->head = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

    stack->head->next = head;

    if (is_stack_empty) {
        stack->max = value;
        stack->head->value = value;
    } else {
        if(value > stack->max) {
            stack->head->value = 2 * value + stack->max;
            stack->max = value;
        } else {
            stack->head->value = value;
        }
    }
}

uint32_t top(stack_t* stack) {

    uint32_t value = stack->head->value;

    if (value > stack->max) {
        value = stack->max;
    }

    return value;
}

uint32_t stack_max(stack_t* stack) {
    return stack->max;
}

uint32_t pop(stack_t* stack) {
    if(!is_empty(stack)) {
        uint32_t value = stack->head->value;

        if (value > stack->max) {
            value = stack->max;
            stack->max = stack->head->value - stack->max * 2;
        }


        linked_list_node_t* head = stack->head->next;
        free(stack->head);
        stack->head = head;

        return value;
    }

    return 0;
}

int main() {
    stack_t stack;
    stack_t* p_stack = &stack;

    new(p_stack);

    push(p_stack, 2);

    printf("Push %d\n", 2);
    printf("Stack max is %d\n", stack_max(p_stack));

    push(p_stack, 3);

    printf("Push %d\n", 3);
    printf("Stack max is %d\n", stack_max(p_stack));

    push(p_stack, 2);

    printf("Push %d\n", 2);
    printf("Stack max is %d\n", stack_max(p_stack));

    push(p_stack, 8);

    printf("Push %d\n", 8);
    printf("Stack max is %d\n", stack_max(p_stack));

    push(p_stack, 2);

    printf("Push %d\n", 2);
    printf("Stack max is %d\n", stack_max(p_stack));

    printf("Pop %d\n", pop(p_stack));
    printf("Stack max is %d\n", stack_max(p_stack));

    printf("Pop %d\n", pop(p_stack));
    printf("Stack max is %d\n", stack_max(p_stack));

    printf("Pop %d\n", pop(p_stack));
    printf("Stack max is %d\n", stack_max(p_stack));

    printf("Pop %d\n", pop(p_stack));
    printf("Stack max is %d\n", stack_max(p_stack));

    delete(p_stack);
}