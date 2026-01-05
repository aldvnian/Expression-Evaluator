#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <stdbool.h>

typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_PARENTHESIS,
    TOKEN_INVALID
} TokenType;

typedef struct {
    TokenType TokenType;
    double value;
    char op;
} Token;

// Function declarations
Token* tokenize(char *str, int *count);

#endif // TOKENIZER_H
