//
// Created by Haim Adrian
//

#ifndef UTILS_STACK_H
#define UTILS_STACK_H

#define TRUE 1
#define FALSE 0
#define INITIAL_STACK_CAPACITY 8

typedef char stackType;

typedef struct {
	int top;
	int capacity;
	/// Dynamic array containing stack elements. This array contains 'capacity' places to store elements.
	/// When we reach to the maximum capacity in this array, we reallocate more places. (1.5 times capacity)
	stackType *elements;
} stack;

int createStack(stack *);

int createStackWithInitialCapacity(stack *, int capacity);

int stackSize(stack *);

int isStackEmpty(stack *);

int isStackFull(stack *);

int push(stack *, stackType);

int pop(stack *, stackType *output);

int top(stack *, stackType *output);

void printStack(stack *);

void freeStack(stack *);

#endif //UTILS_STACK_H