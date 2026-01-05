#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack.h"
#include "tokenizer.h"
#include "infix_to_postfix.h"
#include "evaluate.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s '<expression>'\n", argv[0]);
        return 1;
    }

    int totalLen = 0;
    for (int i = 1; i < argc; i++) {
        totalLen += strlen(argv[i]) + 1;
    }

    char *str = malloc(totalLen);
    if (!str) return 1;

    str[0] = '\0';
    for (int i = 1; i < argc; i++) {
        strcat(str, argv[i]);
        if (i < argc - 1) strcat(str, " ");
    }

    int tokenCount = 0;
    Token *tokens = tokenize(str, &tokenCount);
    if (!tokens) {
        free(str);
        return 1;
    }

    int postfixCount = 0;
    Token *orderedTokens = infix_to_postfix(tokens, tokenCount, &postfixCount);
    if (!orderedTokens) {
        free(str);
        return 1;
    }

    double sum = evaluate(orderedTokens, postfixCount);

    printf("Postfix: ");
    for (int y = 0; y < postfixCount; y++) {
        if (orderedTokens[y].TokenType == TOKEN_NUMBER) {
            printf("%g ", orderedTokens[y].value);
        } else {
            printf("%c ", orderedTokens[y].op);
        }
    }
    printf("\nSum: %g\n", sum);

    free(str);
    // free(tokens); // only if tokenize mallocs separately
    // free(orderedTokens); // only if infix_to_postfix mallocs separately

    return 0;
}
