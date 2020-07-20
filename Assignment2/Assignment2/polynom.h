//
// Created by Haim Adrian
//

#ifndef ASSIGNMENT2_POLYNOMIAL_H
#define ASSIGNMENT2_POLYNOMIAL_H

#include "customdoublelinkedlist.h"

typedef struct polynomial {
    doubleLinkedList_custom *list;
} polynomial;

int initPolynomial(polynomial *p);

void freePolynomial(polynomial *p);

int insertToPolynomial(polynomial *p, polynomialNodeType *item);

int isPolynomialZero(polynomial *p);

polynomial *polyAdd(polynomial *p1, polynomial *p2);

polynomial *polySub(polynomial *p1, polynomial *p2);

polynomial *polyMul(polynomial *p1, polynomial *p2);

polynomial *polyDiv(polynomial *p1, polynomial *p2);

polynomial *polyMulByNum(polynomial *p, int num);

int polyOrderOfMagnitude(polynomial *p);

void printPolynomial(polynomial *p);

polynomial *readPolynomial();

#endif //ASSIGNMENT2_POLYNOMIAL_H
