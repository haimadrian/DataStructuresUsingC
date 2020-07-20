//
// Created by Haim Adrian
//

#ifndef ASSIGNMENT2_ARITHMETICUTIL_H
#define ASSIGNMENT2_ARITHMETICUTIL_H

#define PLUS '+'
#define MINUS '-'
#define MUL '*'
#define DIV '/'
#define POW '^'

// Compare operators based on their rank.
int operatorCompare(char firstOperator, char secondOperator);

// Tells if the specified character is an operand ('A'-'H', '0'-'9')
int isOperand(char c);

// Tells if the specified character is an operator (+, -, *, /, ^)
int isOperator(char c);

// Tells the precedence of an operator.
// Give each operator a ranking so we can compare operators easily.
int rankOperator(char operator);

#endif //ASSIGNMENT2_ARITHMETICUTIL_H
