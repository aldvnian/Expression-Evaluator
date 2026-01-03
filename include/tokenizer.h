typedef enum {
    TOKEN_NUMBER,
    TOKEN_OPERATOR,
    TOKEN_PARENTHESIS
} TokenType;

typedef struct {
    TokenType type;
    char op;      // for operators and parentheses
    double value; // for numbers
} Token;