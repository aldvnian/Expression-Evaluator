#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "tokenizer.h"

bool is_higher_precedence(char op1, char op2);
bool is_valid_expression(Token *tokens, int count);

Token* infix_to_postfix(Token *tokens, int count, int *out_count) {
    Stack *newStack = create_stack(count);
    Token *output = malloc(sizeof(Token) * count);
    int outputCount = 0;

    if (!is_valid_expression(tokens, count)) {
        return NULL;
    }

    for (int x = 0; x < count; x++) {

        if (tokens[x].TokenType == TOKEN_NUMBER) {
            output[outputCount++] = tokens[x];
        }

        else if (tokens[x].TokenType == TOKEN_PARENTHESIS) {

            if (tokens[x].op == '(') {
                push(newStack, &tokens[x]);
            } 
            
            else {

                while (!is_empty(newStack)) {
                    Token *op;
                    pop(newStack, (void**)&op);

                    if (op->op == '(')
                        break;

                    output[outputCount++] = *op;
                }

            }
        }

        else if (tokens[x].TokenType == TOKEN_OPERATOR) {

            Token *top;
            bool has_top = peek(newStack, (void**)&top);

            while (has_top &&
                   top->TokenType == TOKEN_OPERATOR &&
                   is_higher_precedence(top->op, tokens[x].op)) {

                Token *op;
                pop(newStack, (void**)&op);
                output[outputCount++] = *op;

                has_top = peek(newStack, (void**)&top);
            }

            push(newStack, &tokens[x]);
        }
    }

    while (!is_empty(newStack)) {
        Token *op;
        pop(newStack, (void**)&op);
        output[outputCount++] = *op;
    }

    *out_count = outputCount;
    free_stack(newStack);
    return output;
}

int get_precedence(char op) {
    if (op == '+' || op == '-') {
        return 1;
    }
    return 2;
}

bool is_higher_precedence(char op1, char op2) {
    int num1 = get_precedence(op1);
    int num2 = get_precedence(op2);

    if (num1 >= num2) {
        return true;
    }

    return false;
}

bool is_valid_expression(Token *tokens, int count) {
    if (count == 0) return false;

    int paren_balance = 0;

    for (int i = 0; i < count; i++) {
        Token t = tokens[i];

        if (t.TokenType == TOKEN_PARENTHESIS) {
            if (t.op == '(') {
                paren_balance++;
            } else {
                paren_balance--;
                if (paren_balance < 0)
                    return false;
            }
            continue;
        }

        if (t.TokenType == TOKEN_OPERATOR) {
            if (i == 0 || i == count - 1)
                return false;

            Token prev = tokens[i - 1];
            Token next = tokens[i + 1];

            if (!(prev.TokenType == TOKEN_NUMBER ||
                  (prev.TokenType == TOKEN_PARENTHESIS && prev.op == ')')))
                return false;

            if (!(next.TokenType == TOKEN_NUMBER ||
                  (next.TokenType == TOKEN_PARENTHESIS && next.op == '(')))
                return false;

            continue;
        }

        if (t.TokenType == TOKEN_NUMBER) {
            if (i > 0) {
                Token prev = tokens[i - 1];

                if (prev.TokenType == TOKEN_NUMBER)
                    return false;

                if (prev.TokenType == TOKEN_PARENTHESIS && prev.op == ')')
                    return false;
            }
            continue;
        }

        return false;
    }

    return paren_balance == 0;
}

