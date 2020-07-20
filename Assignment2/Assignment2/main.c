/**
* Assigned By
* -----------
* Name: Haim Adrian
* Group: 61104-61
*
* Name: Shlomki Amir
* Group: 61104-61
*/

#include "polynomialtype.h"

// Set it so we will define the custom list type here, and not the default one in customdoublelinkedlist.h
#define CUSTOM_LIST_NODE_TYPE
typedef polynomialNodeType * doubleListNodeType_custom;

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "polynom.h"
#include "table.h"
#include "stack.h"
#include "stringutil.h"
#include "arithmeticutil.h"
#include "safe.h"

#define TRUE 1
#define FALSE 0
#define OPERATIONS_TABLE_COLS 4
#define CHARS 26

#define min(a,b) (((a) < (b)) ? (a) : (b))

typedef int bool;
typedef unsigned int uint;

// Display main menu and return user choose
uint showMainMenu();

/// EX1 ///
void ex1();

// Global table titles, to be available during whole execution of the program.
string tableTitles[OPERATIONS_TABLE_COLS] = {
	"Operation",
	"Operand1",
	"Operand2",
	"Result"
};

// Parses an expression into table of operations. All functions defined below main.
table *parse(string expression);

/// EX2 ///
void ex2();
void basicEx2();
void advancedEx2();

polynomial *doOperationByType(char operation, polynomial *polynomials[CHARS], table *operationsTable, int row);

/// Main ///
int main() {
	uint action;

	do {
		action = showMainMenu();
		switch (action) {
			case 1: ex1(); break;
			case 2: ex2(); break;
			case 0: /* Do nothing. EXIT */ break;
			default: printf("Unknown action: %d. Please try again.\n", action);
		}
		printf("\n");
	} while (action != 0);

	printf("Good bye. Press any key to continue...\n");
	getchar();

	return 0;
}

////////////////////////////// EX1 BEGINNING //////////////////////////////

void ex1() {
	string expression;
	table *operationsTable;

	printf("\nEnter arithmetic expression, constructed out of operands (A-H, 0-9) and operators (+,-,*,/,^):\n");
	expression = readString();

	if (expression) {
		operationsTable = parse(expression);

		printf("\nTable of operations for the expression: %s\n", expression);
		printTable(operationsTable);

		free(expression);

		if (operationsTable) {
			freeTable(operationsTable);
		}
	}
}

// Used by 'parse' method in order to validate every single character in an expression.
// This function can fix lower cased operands - Making them to upper case.
bool validateInput(char *c) {
	bool isValid = TRUE;

	// Fix lowercase letter
	if ((*c >= 'a') && (*c <= 'z')) {
		*c = (char)toupper(*c);
	}

	if (!(isOperand(*c) || isOperator(*c))) {
		isValid = FALSE;
		printf("Illegal expression. Character %c is neither operator (+,-,*,/,^) nor operand (A-H)\n", *c);

		if ((*c >= 'I') && (*c <= 'Z')) {
			printf("Character %c is an application reserved variable. Please use A-H operands.\n", *c);
		}
	}

	return isValid;
}

// Used by 'parse' method when an invalid input is detected.
// We use the 'validateInput' function in order to detect if input is valid. If it is invalid,
// we print an error message and free resources held by 'parse' function.
void handleIllegalExpression(stack *operandsStack, stack *operatorsStack, stack *variablesStack, table *operationsTable) {
	freeStack(operandsStack);
	freeStack(operatorsStack);
	freeStack(variablesStack);
	freeTable(operationsTable);
}

// A utility method created to wrap insertion of a row operation into the operations table.
// A row is of the form: OPERATION | OPERAND1 | OPERAND2 | RESULT
void insertRow(table *operationsTable, tableType operation, tableType op1, tableType op2, tableType result) {
	int rowIndex;
	appendRow(operationsTable, &rowIndex);
	insertValue(operationsTable, rowIndex, 0, operation);
	insertValue(operationsTable, rowIndex, 1, op1);
	insertValue(operationsTable, rowIndex, 2, op2);
	insertValue(operationsTable, rowIndex, 3, result);
}

// Takes top operator from operatorsStack and top two operands from operandsStack.
// Resolve an operation between those popped out items, add the as a row in operations 
// table and push the result variable into operands stack.
// Note that no row will be resolved in case no variables left in the stack of
// application variables (Z-I)
bool resolveOperation(stack *operandsStack, stack *operatorsStack, stack *variablesStack, table *operationsTable) {
	char topOperator, op1, op2, result;

	// At this stage, there must be at least one operator and two operands.
	if (pop(operatorsStack, &topOperator) && pop(operandsStack, &op2) && pop(operandsStack, &op1)) {
		if (!isStackEmpty(variablesStack)) {
			pop(variablesStack, &result);
			insertRow(operationsTable, topOperator, op1, op2, result);
			push(operandsStack, result);
			
			return TRUE;
		} else {
			printf("Application ran out of variables (I-Z). Expression is too long.\n");
		}
	}
	
	return FALSE;
}
// A function that maps an input character into one of two stacks.
// If the input character is an operand, it will be pushed into operandsStack, and the function returns
// FALSE, telling that the input was not an operator.
// Otherwise, if it is an operator, we would like to push it into operatorsStack iff operatorsStack
// is empty, or the operator has a higher precedence than the top of the operators stack. If it got
// a precedence that equal to, or less than the top of the stack, we will pop out the top of the stack
// to resolve an operation (e.g. A*B), and then push a variable (e.g. 'Z' or 'Y') into the operands stack
// and call 'mapInput' recursively in order to continue comparison of the operator 'input' with
// the new top of the operators stack.
int mapInput(char input, stack *operandsStack, stack *operatorsStack, table *operationsTable, stack *variablesStack) {
	char topOperator;

	// If input is an operand, push it into operands stack
	if (isOperand(input)) {
		push(operandsStack, input);
		return FALSE;
	}
	// First check if input is '^', so we will push it to the stack with no conditions. (BONUS - A^(B^C))
	// Top returns FALSE when the stack is empty, so if the operators stack is empty
	// or input got higher precedence than the top operator, we will push input into operatorsStack.
	else if ((input == POW) || (!top(operatorsStack, &topOperator)) || (operatorCompare(input, topOperator) > 0)) {
		push(operatorsStack, input);
	}
	// Otherwise, that means the input is an operator which got same or lower precedence than the top operator.
	else {
		resolveOperation(operandsStack, operatorsStack, variablesStack, operationsTable);

		// Now handle input again, recursively, until we can push the input to the top
		// of the operators stack.
		mapInput(input, operandsStack, operatorsStack, operationsTable, variablesStack);
	}

	// Return TRUE to tell that input was an operator.
	return TRUE;
}

// Returns a stack that contains all of the available variables of the application. ('I'-'Z')
stack *createVariablesStack() {
	stack *variables = (stack *)malloc(sizeof(stack));
	stackType c;

	if (!createStack(variables)) {
		printf("Failed to create stack\n");
		return NULL;
	}

	for (c = 'I'; (int)c <= 'Z'; c++) {
		if (!push(variables, c)) {
			freeStack(variables);
			printf("Failed to push element '%c' to stack\n", c);
			return NULL;
		}
	}

	return variables;
}

// Counting how many operators in an expression, to know how many rows to allocate in the table
uint countOperators(string expression) {
	int strLength = (int)strlen(expression);
	uint operatorsCount = 0;

	while (--strLength >= 0) {
		operatorsCount += isOperator(expression[strLength]);
	}

	return operatorsCount;
}

// The business logic of 'parse' function.
// Here we map every single character from the expression, and also validate the entire
// expression. We use the 'mapInput' function for that.
bool doParseExpression(string expression, stack *operandsStack, stack *operatorsStack, stack *variablesStack, table *operationsTable) {
	uint exprIndex = 0, exprLength = (uint)strlen(expression), lastIndex = exprLength-1;
	bool isOperat, prevIsOperat; // Used for expression validation

	// Skip beginning spaces, in case there are.
	while ((exprIndex < exprLength) && (expression[exprIndex] == ' ')) {
		exprIndex++;
	}
	// Skip ending spaces, in case there are.
	while ((lastIndex > 0) && (expression[lastIndex] == ' ')) {
		lastIndex--;
	}

	// Validate first and last char out of the loop
	if ((!validateInput(&(expression[exprIndex]))) || (!validateInput(&(expression[lastIndex])))) {
		handleIllegalExpression(operandsStack, operatorsStack, variablesStack, operationsTable);
		return FALSE;
	}

	// After validation might have been updated lower cased letter to its upper case form,
	// make sure the first and last characters are operands.
	if ((!isOperand(expression[exprIndex])) || (!isOperand(expression[lastIndex]))) {
		printf("Illegal expression. Beginning and ending characters must be operands. [begin=%c, end=%c]\n", expression[exprIndex], expression[lastIndex]);
		handleIllegalExpression(operandsStack, operatorsStack, variablesStack, operationsTable);
		return FALSE;
	}

	prevIsOperat = mapInput(expression[exprIndex++], operandsStack, operatorsStack, operationsTable, variablesStack);
	for (; exprIndex <= lastIndex; exprIndex++) {
		// Skip spaces
		if (expression[exprIndex] == ' ') {
			continue;
		}

		if (!validateInput(&(expression[exprIndex]))) {
			handleIllegalExpression(operandsStack, operatorsStack, variablesStack, operationsTable);
			return FALSE;
		}

		// Put the input character in s1 or s2, and get a result telling if it was operator.
		isOperat = mapInput(expression[exprIndex], operandsStack, operatorsStack, operationsTable, variablesStack);

		// In case there are two operators or two operands, one by another, that's illegal.
		if (isOperat == prevIsOperat) {
			handleIllegalExpression(operandsStack, operatorsStack, variablesStack, operationsTable);
			printf("Expression cannot contain two or more %s in a row", isOperat ? "operators" : "operands");
			return FALSE;
		}

		prevIsOperat = isOperat;
	}

	return TRUE;
}

// Main functionality - Validate and parse an arithmetic expression. Return the result as a table
table *parse(string expression) {
	table *operationsTable = NULL;
	int operationsTableLength;
	stack *variablesStack, operandsStack /* s1 */, operatorsStack /* s2 */;

	operationsTableLength = countOperators(expression);
	if (operationsTableLength == 0) {
		printf("Illegal expression. No operator could be found, hence do nothing.\n");
	} else {
		variablesStack = createVariablesStack();
		if (!variablesStack) { // assert
			return NULL;
		}

		// If there are more operations than available variables, we calculate the amount
		// of available variables only, and ignore the last operations.
		operationsTableLength = min(operationsTableLength, stackSize(variablesStack));
		operationsTable = createTable(operationsTableLength, OPERATIONS_TABLE_COLS, tableTitles);
		if (!operationsTable) { // assert
			freeStack(variablesStack);
			return NULL;
		}

		if (!createStack(&operandsStack)) { // assert
			printf("Failed to create stack\n");
			freeTable(operationsTable);
			freeStack(variablesStack);
			return NULL;
		}

		if (!createStack(&operatorsStack)) { // assert
			printf("Failed to create stack\n");
			freeTable(operationsTable);
			freeStack(variablesStack);
			freeStack(&operandsStack);
			return NULL;
		}

		// Scan the expression to map operands and operators to their stacks.
		if (!doParseExpression(expression, &operandsStack, &operatorsStack, variablesStack, operationsTable)) {
			// In case expression validation failed, resources already freed inside doParse. return NULL.
			return NULL;
		}

		// Now handle all operations based on operators in the stack.
		while (!isStackEmpty(&operatorsStack)) {
			resolveOperation(&operandsStack, &operatorsStack, variablesStack, operationsTable);
		}

		free(variablesStack);
		freeStack(&operandsStack);
		freeStack(&operatorsStack);
	}

	return operationsTable;
}

///////////////////////////////// EX1 END /////////////////////////////////


////////////////////////////// EX2 BEGINNING //////////////////////////////

// Read polynomials from stdin
void readPolynomials(polynomial **polynomials) {
    int i;
    char continues;

    for (i = 'A'; (int)i <= 'H'; i++) {
        printf("Enter polynomial %c:\n", i);
        polynomials[i - 'A'] = readPolynomial();

        printf("Continue to enter next polynomial? [y/n]\n");
        continues = (char)getchar();
        while (getchar() != '\n');

        if ((continues != 'y') && (continues != 'Y')) {
            break;
        }
    }
}

void printPolynomials(polynomial **polynomials, bool showOrderOfMagnitude, bool freeResults) {
    int i;

	// First print the input
    for (i = 'A'; i <= 'H'; i++) {
        if (polynomials[i - 'A']) {
            printf("%c: ", i);
            printPolynomial(polynomials[i - 'A']);

            if (showOrderOfMagnitude) {
                printf("\t(Order of magnitude: %d)\n", polyOrderOfMagnitude(polynomials[i - 'A']));
            } else {
                printf("\n");
            }
        }
    }

	printf("\n");

	// And then print the results from Z to I
	for (i = 'Z'; i >= 'I'; i--) {
		if (polynomials[i - 'A']) {
			printf("%c: ", i);
			printPolynomial(polynomials[i - 'A']);

			if (showOrderOfMagnitude) {
				printf("\t(Order of magnitude: %d)\n", polyOrderOfMagnitude(polynomials[i - 'A']));
			}
			else {
				printf("\n");
			}

			// Free results for next expression iteration.
			if (freeResults) {
				freePolynomial(polynomials[i - 'A']);
				polynomials[i - 'A'] = NULL;
			}
		}
	}
}

void advancedEx2() {
    polynomial *polynomials[CHARS];
    int i, row;
    char continues, operation;
    string expression;
    table *operationsTable;

    for (i = 0; i < CHARS; i++) {
        polynomials[i] = NULL;
    }

    printf("\nPlease enter polynomials into memory as variables (A-H) and then calculate arithmetic expression.\n");
    printf("Note that power operator is not supported in the polynomial world, and division is supported by single element polynomial only.\n");

    readPolynomials(polynomials);

    do {
        printf("Input polynomials:\n");
        printPolynomials(polynomials, FALSE, FALSE);

        printf("\nEnter arithmetic expression, constructed out of operands (A-H, 0-9) and operators (+,-,*,/), so we will calculate it for input polynomials:\n");
        expression = readString();

        if (expression) {
            // Parse expression to get operations table and use it for polynomial operations
            operationsTable = parse(expression);

            if (operationsTable) {
                printf("\nTable of operations for the expression: %s\n", expression);
                printTable(operationsTable);

                for (row = 0; row < operationsTable->rows; row++) {
                    operation = getValue(operationsTable, row, 0); // First col is operation col
                    polynomials[getValue(operationsTable, row, 3) - 'A'] = doOperationByType(operation, polynomials, operationsTable, row);
                }

                free(expression);
                freeTable(operationsTable);

                printf("\nCalculated polynomials:\n");
                printPolynomials(polynomials, TRUE, TRUE);
            }
        }

        printf("\nWould you like to enter another expression on the same polynomials? [y/n]\n");
        continues = (char)getchar();
        while (getchar() != '\n');
    } while ((continues == 'y') || (continues == 'Y'));

    for (i = 0; i < CHARS; i++) {
        if (polynomials[i]) {
            freePolynomial(polynomials[i]);
        }
    }
}

polynomial *doOperationByType(char operation, polynomial *polynomials[CHARS], table *operationsTable, int row) {
    polynomial *result = NULL, *temp1, *temp2;
	polynomialNodeType *tempAllocForDigits;
    char op1 = getValue(operationsTable, row, 1), op2 = getValue(operationsTable, row, 2);

    if (isdigit(op1)) {
        temp1 = (polynomial *)malloc(sizeof(polynomial));
        initPolynomial(temp1);
		tempAllocForDigits = allocPolynomialNodeValue(op1 - '0', 0);
		if (!insertToPolynomial(temp1, tempAllocForDigits)) {
			// In case it is zero, it won't be accepted by polynomial. Free it.
			freePolynomialNodeType(tempAllocForDigits);
		}
    } else {
        temp1 = polynomials[op1-'A'];
    }

    if (isdigit(op2)) {
        temp2 = (polynomial *)malloc(sizeof(polynomial));
        initPolynomial(temp2);
		tempAllocForDigits = allocPolynomialNodeValue(op2 - '0', 0);
		if (!insertToPolynomial(temp2, tempAllocForDigits)) {
			// In case it is zero, it won't be accepted by polynomial. Free it.
			freePolynomialNodeType(tempAllocForDigits);
		}
    } else {
        temp2 = polynomials[op2-'A'];
    }

    switch (operation) {
        case POW: printf("Power operation is illegal for polynomials.. Zeroes are going to be found.\n"); break;
        case DIV: {
			if (temp2 && (linkedListSize_custom(temp2->list) > 1)) {
				printf("Divide operation is illegal for a divider with more than one item.. Zeroes are going to be found.\n");
			} else {
				result = polyDiv(temp1, temp2);
			}
            break;
        }
        case MUL: result = polyMul(temp1, temp2); break;
        case PLUS: result = polyAdd(temp1, temp2); break;
        case MINUS: result = polySub(temp1, temp2); break;
        default: /* Nothing to do */ break;
    }

    return result;
}

void executeBasicAdd() {
	polynomial *p1 = NULL, *p2 = NULL, *result = NULL;
	p1 = readPolynomial();
	p2 = readPolynomial();
	result = polyAdd(p1, p2);

	printf("(");
	printPolynomial(p1);
	printf(") + (");
	printPolynomial(p2);
	printf(") = ");
	printPolynomial(result);
	printf("\n");

	freePolynomial(p1);
	freePolynomial(p2);
	freePolynomial(result);
}

void executeBasicSub() {
	polynomial *p1 = NULL, *p2 = NULL, *result = NULL;
	p1 = readPolynomial();
	p2 = readPolynomial();
	result = polySub(p1, p2);

	printf("(");
	printPolynomial(p1);
	printf(") - (");
	printPolynomial(p2);
	printf(") = ");
	printPolynomial(result);
	printf("\n");

	freePolynomial(p1);
	freePolynomial(p2);
	freePolynomial(result);
}

void executeBasicMul() {
	polynomial *p1 = NULL, *p2 = NULL, *result = NULL;
	p1 = readPolynomial();
	p2 = readPolynomial();
	result = polyMul(p1, p2);

	printf("(");
	printPolynomial(p1);
	printf(") * (");
	printPolynomial(p2);
	printf(") = ");
	printPolynomial(result);
	printf("\n");

	freePolynomial(p1);
	freePolynomial(p2);
	freePolynomial(result);
}

void executeBasicDiv() {
	polynomial *p1 = NULL, *p2 = NULL, *result = NULL;
	p1 = readPolynomial();
	p2 = readPolynomial();

	// Validate second polynomial is legal
	while (linkedListSize_custom(p2->list) > 1) {
		printf("Division by a polynomial with more than 1 item is not supported. Please enter a single item. Problematic polynomial was: ");
		printPolynomial(p2);
		printf("\n");

		// First free it and then read another one.
		freePolynomial(p2);
		p2 = readPolynomial();
	}

	result = polyDiv(p1, p2);

	printf("(");
	printPolynomial(p1);
	printf(") / (");
	printPolynomial(p2);
	printf(") = ");
	printPolynomial(result);
	printf("\n");

	freePolynomial(p1);
	freePolynomial(p2);
	freePolynomial(result);
}

void executeBasicMulByNum() {
	polynomial *p1 = NULL, *result = NULL;
	int num;
	printf("Enter an integer:\n");
	num = scanIntSafe();
	p1 = readPolynomial();
	result = polyMulByNum(p1, num);

	printf("%d * (", num);
	printPolynomial(p1);
	printf(") = ");
	printPolynomial(result);
	printf("\n");

	freePolynomial(p1);
	freePolynomial(result);
}

void basicEx2() {
    uint action;

	printf("\n");
    do {
        printf("Choose a polynomial action to run or 0 to exit:\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
		printf("4. Division (Second polinomial must have a single node)\n");
        printf("5. Multiply by number\n");
        printf("0. Exit\n");
        action = scanUIntSafe();

        switch (action) {
            case 1: executeBasicAdd(); break;
			case 2: executeBasicSub(); break;
			case 3: executeBasicMul(); break;
			case 4: executeBasicDiv(); break;
			case 5: executeBasicMulByNum(); break;
            case 0: /* Do nothing. EXIT */ break;
            default: printf("Unknown action: %d. Please try again.\n", action);
        }
        printf("\n");
    } while (action != 0);
}

void ex2() {
    uint action;

    printf("\nWelcome to the Polynomial world! Please select a door:\n");
    printf("1. Basic: Show sub menu to select specific polynomial operations\n");
    printf("2. Advanced: Enter polynomials into memory (A,B,...,H) and an arithmetic expression to calculate for them\n");
    printf("0. Exit\n");

    action = scanUIntSafe();

    if (action == 1) {
        basicEx2();
    } else if (action == 2) {
        advancedEx2();
    } else {
        printf("Exiting from the Polynomial world.\n");
    }
}

///////////////////////////////// EX2 END /////////////////////////////////

/// Main Menu ///
uint showMainMenu() {
	printf("Choose an exercise to run or 0 to exit:\n");
	printf("1. Arithmetic expression\n");
	printf("2. Polynomial\n");
	printf("0. Exit\n");

	return scanUIntSafe();
}