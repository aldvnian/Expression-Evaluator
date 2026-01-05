#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "tokenizer.h"
#include "infix_to_postfix.h"

double calculate(Token *first, Token *second, Token *operator);

Token* handle_operator(Stack *stack, Token *op) {
    Token *firstOperand = NULL;
    Token *secondOperand = NULL;

    bool popped = pop(stack, (void **)&firstOperand);
    if (!popped) return NULL;

    popped = pop(stack, (void **)&secondOperand);
    if (!popped) return NULL;

    double value = calculate(firstOperand, secondOperand, op);

    Token *newToken = malloc(sizeof(Token));
    if (!newToken) return NULL;

    newToken->TokenType = TOKEN_NUMBER;
    newToken->value = value;

    return newToken;
}

double evaluate(Token *tokens_list, int count) {
    Stack *newStack = create_stack(count);
    if (!newStack) return 0.0;

    for (int x = 0; x < count; x++) {
        Token *currentToken = &tokens_list[x];

        if (currentToken->TokenType == TOKEN_NUMBER) {
            push(newStack, currentToken);
        }
        else if (currentToken->TokenType == TOKEN_OPERATOR) {
            Token *result = handle_operator(newStack, currentToken);
            if (!result) {
                return 0.0;
            }
            push(newStack, result);
        }
    }

    Token *final = NULL;
    bool popped = pop(newStack, (void **)&final);
    if (!popped || !final) {
        return 0.0;
    }

    double result = final->value;
    free(final);

    return result;
}

double calculate(Token *first, Token *second, Token *operator) {
    double value1 = first->value;
    double value2 = second->value;

    if (operator->op == '+') {
        return value2 + value1;
    }
    else if (operator->op == '-') {
        return value2 - value1;
    }
    else if (operator->op == '*') {
        return value2 * value1;
    }
    else if (operator->op == '/') {
        if (value1 == 0.0) return 0.0;
        return value2 / value1;
    }

    return 0.0;
}
