//
// Created by Haim Adrian
//

#include <stdio.h>
#include <stdlib.h>
#include "polynomialtype.h"

polynomialNodeType *allocPolynomialNodeValue(int coeff, int pow) {
	polynomialNodeType *value;
	value = (polynomialNodeType *)malloc(sizeof(polynomialNodeType));
	if (value) {
		value->coefficient = coeff;
		value->pow = pow;
	}
	else {
		printf("Failed to allocate memory for polynomial node value: (%d, %d)\n", coeff, pow);
	}

	return value;
}

void freePolynomialNodeType(polynomialNodeType *value) {
	if (value) {
		free(value);
	}
}