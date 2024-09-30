#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// data structures
// data structures
typedef struct linked_list_node {
    uint32_t value;
    struct linked_list_node* next;
} linked_list_node_t;

typedef struct stack {
    struct linked_list_node* head;
} stack_t;

// public functions
void new(stack_t* stack, size_t max_size) {
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

void push(stack_t* stack, char value) {
    linked_list_node_t * head = stack->head;

    stack->head = (linked_list_node_t*)malloc(sizeof(linked_list_node_t));

    stack->head->next = head;
    stack->head->value = value;
}

char top(stack_t* stack) {
    return stack->head->value;
}

char pop(stack_t* stack) {
    if(!is_empty(stack)) {
        char value = stack->head->value;
        linked_list_node_t* head = stack->head->next;
        free(stack->head);
        stack->head = head;

        return value;
    }

    return 0;
}

bool check_string(char* string, size_t string_size) {
    stack_t stack;
    stack_t* p_stack = &stack;

    new(p_stack, string_size);

    for (size_t i = 0; i < string_size; i++)
    {
        switch (string[i])
        {
        case '(':
            push(p_stack, string[i]);
            break;
        case '[':
            push(p_stack, string[i]);
            break;
        case '{':
            push(p_stack, string[i]);
            break;

        case ')':
            if (pop(p_stack) != '(')
            {
                delete(p_stack);
                return false;
            }
            break;
        case ']':
            if (pop(p_stack) != '[')
            {
                delete(p_stack);
                return false;
            }
            break;
        case '}':
            if (pop(p_stack) != '{')
            {
                delete(p_stack);
                return false;
            }
            break;

        default:
            break;
        }
    }

    delete(p_stack);
    return true;
}

int main() {

    char good_seq_1[] = "()()()[][]{()}";
    char good_seq_2[] = "((())){{}}[{}]";
    char bad_seq_1[] = "{[)}";
    char bad_seq_2[] = "}{)(";

    printf("check sequense:\n");
    printf(good_seq_1);
    printf("\n");

    if(check_string(good_seq_1, sizeof(good_seq_1) - 1)) {
        printf("right sequense\n\n");
    } else {
        printf("wrong sequense\n\n");
    }

    printf("check sequense:\n");
    printf(good_seq_2);
    printf("\n");

    if(check_string(good_seq_2, sizeof(good_seq_2) - 1)) {
        printf("right sequense\n\n");
    } else {
        printf("wrong sequense\n\n");
    }

    printf("check sequense:\n");
    printf(bad_seq_1);
    printf("\n");

    if(check_string(bad_seq_1, sizeof(bad_seq_1) - 1)) {
        printf("right sequense\n\n");
    } else {
        printf("wrong sequense\n\n");
    }

    printf("check sequense:\n");
    printf(bad_seq_2);
    printf("\n");

    if(check_string(bad_seq_2, sizeof(bad_seq_2) - 1)) {
        printf("right sequense\n\n");
    } else {
        printf("wrong sequense\n\n");
    }

    return 0;
}
