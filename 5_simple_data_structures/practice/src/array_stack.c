#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// data structures
typedef struct stack {
    char* buffer;
    size_t top;
    size_t max_size;
} stack_t;

// public functions
void new(stack_t* stack, size_t max_size) {
    stack->buffer = (char*)malloc(max_size*sizeof(char));
    stack->max_size = max_size;
    stack->top = 0;
}

void delete(stack_t* stack) {
    free(stack->buffer);
}

bool is_empty(stack_t* stack) {
    return stack->top == 0;
}

bool is_full(stack_t* stack) {
    return stack->top == stack->max_size;
}

void push(stack_t* stack, char value) {
    if(!(is_full(stack))) {
        stack->buffer[stack->top] = value;
        stack->top++;
    }
}

char top(stack_t* stack) {
    return stack->buffer[stack->top - 1];
}

char pop(stack_t* stack) {
    if(!is_empty(stack)) {
        stack->top--;
        return stack->buffer[stack->top];
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
