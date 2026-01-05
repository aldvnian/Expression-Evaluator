#ifndef INFIX_TO_POSTFIX_H
#define INFIX_TO_POSTFIX_H

#include "tokenizer.h"

Token* infix_to_postfix(Token *tokens, int count, int *out_count);

#endif // INFIX_TO_POSTFIX_H
