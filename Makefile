CC = gcc
CFLAGS = -Wall -Wextra -std=c11 -Iinclude

SRC = src/stack.c src/tokenizer.c src/infix_to_postfix.c src/evaluator.c src/main.c
OUT = evaluator

all:
	$(CC) $(CFLAGS) $(SRC) -o $(OUT)

clean:
	rm -f $(OUT)
