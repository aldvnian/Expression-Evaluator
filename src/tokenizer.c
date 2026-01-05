#include <ctype.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"
#include "tokenizer.h"
#include "infix_to_postfix.h"
#include <stdlib.h>

Token create_token(void *item, bool is_numeric);

Token* tokenize(char *str, int *count) {
    *count = 0;
    Token *token_list = malloc(sizeof(Token));
    int nr_of_tokens = 0;
    int len = strlen(str);

    for (int x = 0; x < len; x++) {
        if (!isspace(str[x])) {
            Token newToken;

            if (!isdigit(str[x])) {
                newToken = create_token(&str[x], false);
            }
            else {
                int y = x;

                bool point_seen = false;
                while (y < len && (isdigit(str[y]) || (str[y] == '.' && !point_seen))) {
                    if (str[y] == '.') {
                        point_seen = true;
                    }
                    y++;
                }

                int num_len = y - x;
                char *newString = malloc(sizeof(char) * (num_len + 1));

                for (int i = 0; i < num_len; i++) {
                    newString[i] = str[x + i];
                }
                newString[num_len] = '\0';

                newToken = create_token(newString, true);
                free(newString);

                x = y - 1;   // important fix
            }

            token_list[nr_of_tokens++] = newToken;
            *count += 1;
            Token *temp = realloc(token_list, sizeof(Token) * (nr_of_tokens + 1));
            if (!temp) {
                free(token_list);
                return NULL;
            }
            token_list = temp;
        }
    }

    return token_list;
}


// Converts a numeric string (integer or decimal) to a double
double string_to_dec(char *str) {
    double value = 0.0;
    bool is_decimal = false;
    int length = strlen(str);

    // Check if the string contains a decimal point
    for (int i = 0; i < length; i++) {
        if (str[i] == '.') {
            is_decimal = true;
            break;
        }
    }

    if (!is_decimal) {
        // Integer conversion
        for (int i = 0; i < length; i++) {
            value += (str[i] - '0') * pow(10, length - i - 1);
        }
    } else {
        // Decimal conversion: split mantissa and fraction
        char temp[strlen(str) + 1];
        strcpy(temp, str);               // copy because strtok modifies string
        char *mantissa = strtok(temp, ".");
        char *fraction = strtok(NULL, ".");

        int mantissa_length = strlen(mantissa);
        int fraction_length = strlen(fraction);

        // Convert mantissa
        for (int i = 0; i < mantissa_length; i++) {
            value += (mantissa[i] - '0') * pow(10, mantissa_length - i - 1);
        }

        // Convert fraction
        for (int i = 0; i < fraction_length; i++) {
            value += (fraction[i] - '0') * pow(10, -(i + 1));
        }
    }

    return value;
}

Token create_token(void *item, bool is_numeric) {
    Token newToken;

    if (is_numeric) {
        newToken.TokenType = TOKEN_NUMBER;
        newToken.value = string_to_dec((char *)item); // use helper function
    }
    else if (*(char *)item == '+' || *(char *)item == '-' ||
             *(char *)item == '*' || *(char *)item == '/') {
        newToken.TokenType = TOKEN_OPERATOR;
        newToken.op = *(char *)item;
    }
    else if (*(char *)item == '(' || *(char *)item == ')') {
        newToken.TokenType = TOKEN_PARENTHESIS;
        newToken.op = *(char *)item;
    }
    else {
        newToken.TokenType = TOKEN_INVALID;
    }

    return newToken;
}
