//
// Created by Haim Adrian
//

#ifndef INC_19_08_02_STACK_H
#define INC_19_08_02_STACK_H

#define TRUE 1
#define FALSE 0
#define INITIAL_STACK_CAPACITY 8

// Type of elements in the stack (char) - Name it as stackType
// Usage: stackType item = 'A';
typedef char stackType;

/// Stack definition.
/// Usage:
/// stack st;
/// createStack(&st);
/// stackPush(&st, 'A');
typedef struct {
	/// Index of head of the stack, or -1 when stack is empty.
	/// We also use top in order to find out the size of the stack. size=top+1.
	int top;

	/// How many places we have in our dynamic array.
	int capacity;

	/// Dynamic array containing stack elements. This array contains 'capacity' places to store elements.
	/// When we reach to the maximum capacity in this array, we reallocate more places. (1.5 times capacity)
	stackType *elements;
} stack;

/// Creates a new stack.
/// Usage: <br/>
/// <code>
/// stack st; <br/>
/// if (!createStack(&st)) { <br/>
/// &nbsp  printf("Failed to create stack"); <br/>
/// }
/// </code>
int createStack(stack *);

/// Creates a new stack with custom initial capacity. Use this when size of the stack is known.
/// Usage: <br/>
/// <code>
/// stack st; <br/>
/// if (!createStackWithInitialCapacity(&st, 10)) { <br/>
/// &nbsp  printf("Failed to create stack"); <br/>
/// }
/// </code>
int createStackWithInitialCapacity(stack *, int);

/// Gets the size of a stack.
/// Usage: <br/>
/// <code>
/// int stackLength = stackSize(st);
/// </code>
int stackSize(stack *);

/// Tells if a stack is empty or not.
/// Usage: <br/>
/// <code>
/// if (isStackEmpty(st)) { <br/>
/// &nbsp  printf("Stack is empty"); <br/>
/// } <br/>
/// freeStack(&st);
/// </code>
int isStackEmpty(stack *);

/// Tells if a stack is full or not. Stack is full when its size equals to its capacity.
/// Usage: <br/>
/// <code>
/// if (isStackFull(st)) { <br/>
/// &nbsp  printf("Stack is full"); <br/>
/// } <br/>
/// freeStack(&st);
/// </code>
int isStackFull(stack *);

/// Push an element into a stack
/// Usage: <br/>
/// <code>
/// stack st; <br/>
/// createStack(&st); <br/>
/// if (stackPush(&st, 'A')) { <br/>
/// &nbsp  printf("Succeeded"); <br/>
/// } else { <br/>
/// &nbsp  printf("Failed"); <br/>
/// } <br/>
/// freeStack(&st);
/// </code>
int stackPush(stack *, stackType);

/// Pop an element out of a stack
/// Usage: <br/>
/// <code>
/// stack st; <br/>
/// stackType item; <br/>
/// createStack(&st); <br/>
/// if (stackPush(&st, 'A')) { <br/>
/// &nbsp if (stackPop(&st, &item)) { <br/>
/// &nbsp&nbsp    printf("Succeeded. Element is %c", item); <br/>
/// &nbsp  } else { <br/>
/// &nbsp&nbsp    printf("Failed to pop an element"); <br/>
/// &nbsp  } <br/>
/// } else { <br/>
/// &nbsp  printf("Failed to push an element"); <br/>
/// } <br/>
/// freeStack(&st);
/// </code>
int stackPop(stack *, stackType *output);

/// Peak an element of a stack. This looks at the head of the stuck, without popping it out.
/// Usage: <br/>
/// <code>
/// stack st; <br/>
/// stackType item; <br/>
/// createStack(&st); <br/>
/// if (stackPush(&st, 'A')) { <br/>
/// &nbsp if (stackHead(st, &item)) { <br/>
/// &nbsp&nbsp    printf("Succeeded. Element is %c", item); <br/>
/// &nbsp  } else { <br/>
/// &nbsp&nbsp    printf("Failed to peak an element"); <br/>
/// &nbsp  } <br/>
/// } else { <br/>
/// &nbsp  printf("Failed to push an element"); <br/>
/// } <br/>
/// freeStack(&st);
/// </code>
int stackHead(stack *, stackType *output);

/// Prints a stack in stack format. (Each element will be printed to its own row).
/// Usage: </br>
/// <code>
/// stack st; <br/>
/// createStack(&st); </br>
/// printStack(st); <br/>
/// freeStack(&st);
/// </code>
void printStack(stack);

/// Free a stack that was previously created.
/// Usage: <br/>
/// <code>
/// stack st; <br/>
/// createStack(&st); <br/>
/// freeStack(&st);
/// </code>
void freeStack(stack *);

#endif //INC_19_08_02_STACK_H