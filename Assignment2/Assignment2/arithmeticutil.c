//
// Created by Haim Adrian
//

#include "arithmeticutil.h"

int isOperand(char c) {
	// Check supported ranges.
	return ((c >= 'A') && (c <= 'H')) || ((c >= '0') && (c <= '9'));
}

int isOperator(char c) {
	// If it is not an operator, rankOperator will give us 0.
	return rankOperator(c) > 0;
}

// Give each operator a ranking so we can compare operators easily.
// This function tells the precedence of an operator.
int rankOperator(char operator) {
	int result;

	switch (operator) {
		case POW:
			result = 3;
			break;
		case MUL:
		case DIV: {
			result = 2;
			break;
		}
		case PLUS:
		case MINUS: {
			result = 1;
			break;
		}
		default:
			result = 0;
			break;
	}

	return result;
}

// Function to compare between two operators.
// If first operator has higher precedence than second operator, a positive value is returned.
// If both operators have equal precedence, 0 is returned.
// If first operator has lower precedence than second operator, a negative value is returned.
int operatorCompare(char firstOperator, char secondOperator) {
	return rankOperator(firstOperator) - rankOperator(secondOperator);
}