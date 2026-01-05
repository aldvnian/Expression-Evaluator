# Expression Evaluator

<br>

## Overview

This is a C-based arithmetic expression evaluator that supports:

- Infix expressions (e.g., 3 + 5 * 2)

- Conversion to postfix notation internally for evaluation

- Basic arithmetic operators: +, -, *, /

- Parentheses for grouping: ()
<br>

The program parses, validates, and evaluates the expression provided via the command line.


## Features

- Tokenization: Splits the input string into numbers, operators, and parentheses.

- Infix to Postfix Conversion: Converts standard mathematical expressions into Reverse Polish Notation for easier evaluation.

- Stack-based Evaluation: Uses a stack to handle operator precedence and compute results correctly.

- Command-line usage: Run any arithmetic expression directly from the terminal.

<br>

## Building the Project

Make sure you are in the src folder. Compile with:

- *gcc -Wall -Wextra -std=c11 -I../include *.c -o calculator -lm**


Note: -lm links the math library (used for pow()).

<br>

## Running the Program

You can evaluate an expression by passing it as a command-line argument:

- ./calculator "3 + 5 * 2"
<br>

**Output:**

- Postfix: 3.000000 5.000000 2.000000 * +
- Sum: 13.000000
<br>

You can also pass multi-word expressions by quoting them.

<br>

**Example Expressions**
- ./calculator "10 / 2 + 7"
- ./calculator "(3 + 5) * 2"
- ./calculator "2 ^ 3 + 1"

<br>

## Implementation Details

- Token struct stores numbers, operators, and parentheses.

- Stack is implemented to handle operands during evaluation.

- Evaluation algorithm uses postfix (Reverse Polish Notation) for correctness with operator precedence.
  
- Infix to Postfix conversion implements the Shunting Yard Algorithm

- Validates expressions before computing to catch syntax errors like consecutive operators or unmatched parentheses.
