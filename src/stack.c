#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

Stack* create_stack(int initial_capacity) {
    Stack *newStack = malloc(sizeof(Stack));
    if (!newStack) return NULL;

    newStack->data = malloc(sizeof(void*) * initial_capacity);
    if (!newStack->data) {
        free(newStack);
        return NULL;
    }

    newStack->top = -1;
    newStack->capacity = initial_capacity;

    return newStack;
}

void free_stack(Stack *stack) {
    free(stack->data);
    free(stack);
}

bool push(Stack *stack, void* value) {
    if (!stack) {
        return false;
    }

    if (stack->top + 1 < stack->capacity) {
        stack->data[stack->top + 1] = value;
        stack->top += 1;
        return true;
    }

    void **newData = realloc(stack->data, (sizeof(void*) * stack->capacity)*2);
    if (!newData) {
        return false;
    }

    newData[stack->top + 1] = value;
    stack->capacity *= 2;
    stack->data = newData;
    stack->top += 1;
    return true;
}

bool pop(Stack *stack, void **value) {
    if (!stack || !value) {
        return false;
    }

    *value = stack->data[stack->top];
    stack->top--;
    return true;
}

bool peek(Stack *stack, void **value) {
    if (!stack || stack->top == -1) {
        return false;
    }

    *value = stack->data[stack->top];
    return true;
}

bool is_empty(Stack *stack) {
    if (stack->top == -1) {
        return true;
    }
    return false;
}