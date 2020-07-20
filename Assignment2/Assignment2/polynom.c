//
// Created by Haim Adrian
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "polynom.h"
#include "customdoublelinkedlist.h"
#include "safe.h"

#define TRUE 1
#define FALSE 0

int initPolynomial(polynomial *p) {
    int success = FALSE;

    if (p) {
        p->list = (doubleLinkedList_custom *) malloc(sizeof(doubleLinkedList_custom));
        if (p->list) {
            success = initLinkedList_custom(p->list);
        }
    }

    return success;
}

void freePolynomial(polynomial *p) {
    if (p) {
        freeLinkedList_custom(p->list, freePolynomialNodeType);
        free(p);
    }
}

// Custom list does not aware that it holds a pointer as value, so we need to free it by ourselves.
void freePolynomialNode(polynomial *p, doubleListNode_custom *node) {
    removeFromList_custom(p->list, node, freePolynomialNodeType);
}

// We compare polynomial nodes by their power value.
// We use this function as a pointer that we pass to findFirst_custom function, which iterates the list of a polynomial and compare
// items to detect when there is a need to stop iterating. We want to stop iteration and return the node once we find a node which
// got a higher or equal power to item2. We use it in order to know where we should insert item2 so we can keep the polynomial sorted.
int comparePolynomialItems(polynomialNodeType *item1, polynomialNodeType *item2) {
    return item1->pow >= item2->pow;
}

int insertToPolynomial(polynomial *p, polynomialNodeType *item) {
    int addedNew = FALSE; // FALSE means merged or illegal state.
    doubleListNode_custom *biggerOrEqualPowNode;
    doubleListNodeType_custom value;

    // We disallow NULL or 0 coefficient values.
    if ((item) && (p) && (item->coefficient != 0)) {
        if (isLinkedListEmpty_custom(p->list)) {
            addedNew = addFirst_custom(p->list, item);
        } else {
            biggerOrEqualPowNode = findFirst_custom(p->list, item, &comparePolynomialItems); // O(n)
            if (biggerOrEqualPowNode) {
                value = value_custom(biggerOrEqualPowNode);

                // If there is a need to aggregate coefficients
                if (value->pow == item->pow) {
                    addedNew = FALSE;
					if (!addIntSafe(value->coefficient, item->coefficient, &(value->coefficient))) {
						value->coefficient = 0;
					}

                    // If aggregation brought us to illegal state (coefficient=0), delete it.
                    if (value->coefficient == 0) {
                        freePolynomialNode(p, biggerOrEqualPowNode);
                    }
                }
                    // In case biggerOrEqualPowNode got a higher power than item, we need to insert item before.
                else {
                    addedNew = insertBefore_custom(p->list, biggerOrEqualPowNode, item);
                }
            }
                // In case there is no bigger or equal node, just append to the end of the list cause item is the biggest node now.
            else {
                addedNew = addLast_custom(p->list, item);
            }
        }
    }

    return addedNew;
}

// A utility function used in order to insert all items of a polynomial (from) into the "to" polynomial.
// This does not use the same nodes, but creates new nodes at "to" polynomial for each value of "from".
void processAddition(polynomial *from, polynomial *to) {
    doubleListNode_custom *iter;
    doubleListNodeType_custom value;
    polynomialNodeType *newValue;

    if (from && to) {
        iter = linkedListIterator_custom(from->list);
        while (iter != NULL) {
            value = value_custom(iter);
            newValue = allocPolynomialNodeValue(value->coefficient, value->pow);

            // Insert into polynomial. If the result is FALSE, it means we failed to insert or the item has been merged into existing node
            // in the polynomial. In this case, we want to free the newly allocated value.
            if (!insertToPolynomial(to, newValue)) {
                freePolynomialNodeType(newValue);
            }

            iter = next_custom(iter);
        }
    }
}

polynomial *polyAdd(polynomial *p1, polynomial *p2) {
    polynomial *sum;

    sum = (polynomial *) malloc(sizeof(polynomial));
    if (initPolynomial(sum)) {
        processAddition(p1, sum);
        processAddition(p2, sum);
    }

    return sum;
}

// A utility function used in order to insert all items of a polynomial (sub) with opposite sign (mul by -1) into the "from" polynomial.
// This does not use the same nodes, but creates new nodes at "from" polynomial for each value of "sub".
void processSubtraction(polynomial *sub, polynomial *from) {
    doubleListNode_custom *iter;
    doubleListNodeType_custom value;
    polynomialNodeType *newValue;
	int coeff;

    if (sub && from) {
        iter = linkedListIterator_custom(sub->list);
        while (iter != NULL) {
            value = value_custom(iter);
			
			// When we multiply minimum integer by -1, we get out of integer range. Hence do it safe.
			if (!mulIntSafe(value->coefficient, -1, &coeff)) {
				coeff = 0;
			}

            newValue = allocPolynomialNodeValue(coeff, value->pow);

            // Insert into polynomial. If the result is FALSE, it means we failed to insert or the item has been merged into existing node
            // in the polynomial. In this case, we want to free the newly allocated value.
            if (!insertToPolynomial(from, newValue)) {
                freePolynomialNodeType(newValue);
            }

            iter = next_custom(iter);
        }
    }
}

polynomial *polySub(polynomial *p1, polynomial *p2) {
    polynomial *sum;

    sum = (polynomial *) malloc(sizeof(polynomial));
    if (initPolynomial(sum)) {
        processAddition(p1, sum);
        processSubtraction(p2, sum);
    }

    return sum;
}

polynomial *polyMul(polynomial *p1, polynomial *p2) {
    doubleListNode_custom *iter1, *iter2;
    doubleListNodeType_custom value1, value2;
    polynomialNodeType *newValue;
    polynomial *result = NULL;
	int coeff, pow;

    result = (polynomial *) malloc(sizeof(polynomial));
    if (initPolynomial(result)) {
        // If any of the specified polynomials is zero, return zero.
        if ((!isPolynomialZero(p1)) && (!isPolynomialZero(p2))) {
            iter1 = linkedListIterator_custom(p1->list);
            while (iter1 != NULL) {
                value1 = value_custom(iter1);

                iter2 = linkedListIterator_custom(p2->list);
                while (iter2 != NULL) {
                    value2 = value_custom(iter2);

					if (!mulIntSafe(value1->coefficient, value2->coefficient, &coeff)) {
						coeff = 0;
					}

					if (!addIntSafe(value1->pow, value2->pow, &pow)) {
						pow = coeff = 0;
					}

                    newValue = allocPolynomialNodeValue(coeff, pow);

                    // Insert into polynomial. If the result is FALSE, it means we failed to insert or the item has been merged into existing node
                    // in the polynomial. In this case, we want to free the newly allocated value.
                    if (!insertToPolynomial(result, newValue)) {
                        freePolynomialNodeType(newValue);
                    }

                    iter2 = next_custom(iter2);
                }

                iter1 = next_custom(iter1);
            }
        }
    }

    return result;
}

polynomial *polyDiv(polynomial *p1, polynomial *p2) {
	doubleListNode_custom *iter1, *item;
	doubleListNodeType_custom value1, value2;
	polynomialNodeType *newValue;
	polynomial *result = NULL;
	int coeff, pow;

	if (isPolynomialZero(p2)) {
		printf("Division of polynomial ");
		printPolynomial(p1);
		printf(" was ignored due to a try to divide by zero. Returning NULL.\n");
	} else {
		result = (polynomial *)malloc(sizeof(polynomial));
		if (initPolynomial(result)) {
			// If polynomial is zero, the result is zero, so avoid of calculations.
			if (!isPolynomialZero(p1)) {
				if (linkedListSize_custom(p2->list) > 1) {
					printf("Cannot divide a polynomial by another polynomial with more than one item. Problematic polynomial: ");
					printPolynomial(p2);
					printf("\n");
				} else if (head_custom(p2->list, &item)) {
					value2 = value_custom(item);
					iter1 = linkedListIterator_custom(p1->list);

					while (iter1 != NULL) {
						value1 = value_custom(iter1);

						coeff = value1->coefficient / value2->coefficient;
						if (!subIntSafe(value1->pow, value2->pow, &pow)) {
							pow = coeff = 0;
						}

						newValue = allocPolynomialNodeValue(coeff, pow);

						// Insert into polynomial. If the result is FALSE, it means we failed to insert or the item has been merged into existing node
						// in the polynomial. In this case, we want to free the newly allocated value.
						if (!insertToPolynomial(result, newValue)) {
							freePolynomialNodeType(newValue);
						}


						iter1 = next_custom(iter1);
					}
				}
			}
		}
	}

	return result;
}

polynomial *polyMulByNum(polynomial *p, int num) {
    doubleListNode_custom *iter;
    doubleListNodeType_custom value;
    polynomialNodeType *newValue;
    polynomial *result = NULL;
	int coeff;

    if (p) {
        result = (polynomial *) malloc(sizeof(polynomial));
        if (initPolynomial(result)) {
            iter = linkedListIterator_custom(p->list);
            while (iter != NULL) {
                value = value_custom(iter);

				if (!mulIntSafe(value->coefficient, num, &coeff)) {
					coeff = 0;
				}

                newValue = allocPolynomialNodeValue(coeff, value->pow);

                // Insert into polynomial. If the result is FALSE, it means we failed to insert or the item has been merged into existing node
                // in the polynomial. In this case, we want to free the newly allocated value.
                if (!insertToPolynomial(result, newValue)) {
                    freePolynomialNodeType(newValue);
                }

                iter = next_custom(iter);
            }
        }
    }

    return result;
}

int polyOrderOfMagnitude(polynomial *p) {
    doubleListNode_custom *tail;

    if (isPolynomialZero(p)) {
        return -1;
    }

    // As the polynomial is sorted, we can return the power of the last element in the list.
    tail_custom(p->list, &tail);
    return value_custom(tail)->pow;
}

int isPolynomialZero(polynomial *p) {
    return (p == NULL) || isLinkedListEmpty_custom(p->list);
}

// A helper procedure used to print a value without sign.
void printPolynomialNodeType(polynomialNodeType *value) {
    int coefficient, pow;

    coefficient = abs(value->coefficient);
    pow = value->pow;

    if ((coefficient != 1) || (pow == 0)) {
        printf("%d", coefficient);
    }

    if (pow == 1) {
        printf("x");
    } else if (pow != 0) {
        printf("x^%d", pow);
    }
}

void printPolynomial(polynomial *p) {
    doubleListNode_custom *iter;
    polynomialNodeType *value;

	if (!p) {
		printf("NaP (Not a Polynomial)");
	} else if (isPolynomialZero(p)) {
        printf("Zero (Empty Polynomial)");
    } else {
        // Order of polynomial items is from highest power to lowest power.
        iter = linkedListIteratorReversed_custom(p->list);

        // Handle first item separately to avoid of printing its sign in case of positive coefficient.
        value = value_custom(iter);
        if (value->coefficient < 0) {
            printf("-");
        }

        printPolynomialNodeType(value);

        while ((iter = iter->prev) != NULL) {
            value = value_custom(iter);

            if (value->coefficient > 0) {
                printf(" + ");
            } else {
                printf(" - ");
            }

            printPolynomialNodeType(value);
        }
    }

}

polynomial *readPolynomial() {
    polynomial *result = (polynomial *) malloc(sizeof(polynomial));
	polynomialNodeType *input;
    int coeff, pow;

    if (initPolynomial(result)) {
        printf("Please enter coefficient and power of polynomial, one by another, as much as you want. Enter 0 coefficient to stop the input.\n");
        while ((coeff = scanIntSafe()) != 0) {
            pow = scanIntSafe();

			input = allocPolynomialNodeValue(coeff, pow);

			if (input) {
				insertToPolynomial(result, input);
			}
        }
    }

    return result;
}