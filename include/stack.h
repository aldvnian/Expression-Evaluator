#ifndef STACK_H
#define STACK_H

#include <stdbool.h>  // for bool

// Stack structure for doubles (to handle numbers)
typedef struct {
    void **data;    // dynamic array to hold stack elements
    int top;         // index of the top element
    int capacity;    // current allocated size
} Stack;

// Function prototypes
Stack* create_stack(int initial_capacity);
void free_stack(Stack *stack);
bool push(Stack *stack, void* value);
bool pop(Stack *stack, void **value);
bool peek(Stack *stack, void **value);
bool is_empty(Stack *stack);

#endif