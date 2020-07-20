//
// Created by Haim Adrian
//

#ifndef ASSIGNMENT2_POLYNOMIALTYPE_H
#define ASSIGNMENT2_POLYNOMIALTYPE_H

typedef struct polynomialNodeType {
	int coefficient;
	int pow;
} polynomialNodeType;


polynomialNodeType *allocPolynomialNodeValue(int coeff, int pow);
void freePolynomialNodeType(polynomialNodeType *value);

#endif //ASSIGNMENT2_POLYNOMIALTYPE_H
