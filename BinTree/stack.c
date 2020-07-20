//
// Created by Haim Adrian on 25-Aug-19.
//

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>

///////// Stack implementation /////////

int createStackWithInitialCapacity(stack *stack1, int capacity) {
	stack1->top = -1;
	stack1->capacity = capacity;
	stack1->elements = (stackType *)malloc(stack1->capacity * sizeof(stackType));

	return stack1->elements != NULL;
}

int createStack(stack *stack1) {
	return createStackWithInitialCapacity(stack1, INITIAL_STACK_CAPACITY);
}

int stackSize(stack *stack1) {
	return stack1->top + 1;
}

int isStackEmpty(stack *stack1) {
	return stack1->top < 0;
}

int isStackFull(stack *stack1) {
	return (stackSize(stack1) == stack1->capacity);
}

int push(stack *stack1, stackType element) {
	int success = TRUE;
	int prevCapacity;
	stackType *elementsBackup;

	// If stack is full, enlarge its capacity
	if (isStackFull(stack1)) {
		elementsBackup = stack1->elements;
		prevCapacity = stack1->capacity;
		stack1->capacity = (int)(stack1->capacity * 1.5);
		stack1->elements = realloc(stack1->elements, stack1->capacity * sizeof(stackType));

		// Rollback in case we could not enlarge the capacity of the stack.
		if (!(stack1->elements)) {
			success = FALSE;
			stack1->elements = elementsBackup;
			stack1->capacity = prevCapacity;
		}
	}

	if (success) {
		stack1->top++;
		stack1->elements[stack1->top] = element;
	}

	return success;
}

int top(stack *stack1, stackType *element) {
	int success = (!isStackEmpty(stack1));
	if (success) {
		*element = stack1->elements[stack1->top];
	}
	return success;
}

int pop(stack *stack1, stackType *element) {
	int success = (!isStackEmpty(stack1));
	if (success) {
		*element = stack1->elements[stack1->top];
		(stack1->top)--;
	}
	return success;
}

void printStack(stack *stack1) {
	int i, stack1Size;
	stack tempStack;
	stackType element;

	stack1Size = stackSize(stack1);
	createStackWithInitialCapacity(&tempStack, stack1Size);

	for (i = stack1Size; i < stack1->capacity; i++) {
		printf("|       |\n");
	}

	for (i = 0; i < stack1Size; i++) {
		pop(stack1, &element);
		push(&tempStack, element); // backup
		printf("| %5d |\n", treeData(element));
	}

	printf("-\"-------\"-  (size=%d, capacity=%d)\n", stack1Size, stack1->capacity);

	// restore
	while (pop(&tempStack, &element)) {
		push(stack1, element);
	}

	freeStack(&tempStack);
}

int readStack(stack *stack1) {
	int n;
	int success;
	stackType item;

	printf("Enter amount of characters to scan into stack:\n");
	scanf_s("%d%*c", &n);
	success = (n > 0) && createStackWithInitialCapacity(stack1, n);

	if (success) {
		printf("Enter %d items:\n", n);
		while (n-- > 0) {
			scanf_s("%c%*c", &item, sizeof(stackType));
			push(stack1, item);
		}
	}

	return success;
}

void freeStack(stack *stack1) {
	//printf("Free stack. [top=%d, capacity=%d, items=%s]\n", stack1->top, stack1->capacity, stack1->elements);
	free(stack1->elements);
}