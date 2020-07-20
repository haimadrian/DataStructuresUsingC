//
// Created by Haim Adrian
//

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "queue.h"

typedef int bool;

///////// Exc /////////
bool readQueue(queue *queue1);
int readAction();
void ex1();
bool isSymmetrical(queue queue1, queue queue2);

void ex2();
bool isIdentical(queue queue1, queue queue2);

void ex3();
void sortStackUsingQueue(stack *stack1);

void ex4();
void sortStackUsingStack(stack *stack1);


///////// Main /////////
int main() {
	int action;

	do {
		action = readAction();
		switch (action) {
			case 1: {
				ex1();
				break;
			}
			case 2: {
				ex2();
				break;
			}
			case 3: {
				ex3();
				break;
			}
			case 4: {
				ex4();
				break;
			}
			case 0: {
				// Exit
				break;
			}
			default: {
				printf("Invalid action: %d.\n", action);
			}
		}
		printf("\n");
	} while (action != 0);

	printf("Bye, thanks. Press any key to continue...\n");
	getchar();

	return 0;
}

bool readQueue(queue *queue1) {
    int n, success;
    queueType item;

    success = createQueue(queue1);

    if (success) {
        printf("Enter amount of characters to scan into queue:\n");
        scanf_s("%d%*c", &n);

        printf("Enter %d items:\n", n);
        while (n-- > 0) {
            scanf_s("%c%*c", &item, sizeof(queueType));
            enqueue(queue1, item);
        }
    }

    return success;
}

bool readStack(stack *stack1) {
    int n;
    bool success;
    stackType item;

    printf("Enter amount of characters to scan into stack:\n");
    scanf_s("%d%*c", &n);
    success = (n > 0) && createStackWithInitialCapacity(stack1, n);

    if (success) {
        printf("Enter %d items:\n", n);
        while (n-- > 0) {
            scanf_s("%c%*c", &item, sizeof(stackType));
            stackPush(stack1, item);
        }
    }

    return success;
}

// Ex1
void ex1() {
	queue queue1, queue2;
    bool isSymmetric;

	printf("############### Exercise 1: Symmetrical Queues ###############\n");
	readQueue(&queue1);
	readQueue(&queue2);

    isSymmetric = isSymmetrical(queue1, queue2);
    printf("First queue:\n");
    printQueue(queue1);

    printf("Second queue:\n");
    printQueue(queue2);

	printf("The queues are %ssymmetrical.\n", isSymmetric ? "" : "not ");
}

bool isSymmetrical(queue queue1, queue queue2) {
	int iterations = 0;
    bool result;
	stack stack1;
	stackType element;
	queueType item;

    // First compare by queue size, which costs O(1)
	result = (queueSize(&queue1) == queueSize(&queue2));

	if (result) {
        createStackWithInitialCapacity(&stack1, queueSize(&queue2));

        // Push all elements of second queue to a stack. O(n)
        while (!isQueueEmpty(&queue2)) {
            iterations++;
            dequeue(&queue2, &item);
            stackPush(&stack1, item);
        }

        // Additional O(n)
        while ((!isQueueEmpty(&queue1)) && result) {
            iterations++;
            dequeue(&queue1, &item);
            stackPop(&stack1, &element);

            result = (item == element);
        }

        freeStack(&stack1);
    }

    printf("There were %d iterations. Time complexity: O(n)\n", iterations ? iterations : 1);

	return result;
}

// Ex2
void ex2() {
    queue queue1, queue2;
    bool isSame;

    printf("############### Exercise 2: Identical Queues ###############\n");
    readQueue(&queue1);
    readQueue(&queue2);

    isSame = isIdentical(queue1, queue2);
    printf("First queue:\n");
    printQueue(queue1);

    printf("Second queue:\n");
    printQueue(queue2);

    printf("The queues are %sidentical.\n", isSame ? "" : "not ");
}

bool isIdentical(queue queue1, queue queue2) {
    int iterations = 0;
    bool result;
    queueType item1;
    queueType item2;

    // First compare by queue size, which costs O(1)
    result = (queueSize(&queue1) == queueSize(&queue2));

    if (result) {
        // O(n)
        while ((!isQueueEmpty(&queue1)) && result) {
            iterations++;
            dequeue(&queue1, &item1);
            dequeue(&queue2, &item2);

            result = (item1 == item2);
        }
    }

    printf("There were %d iterations. Time complexity: O(n)\n", iterations ? iterations : 1);

    return result;
}

// Ex3
void ex3() {
    stack stack1;

	printf("############### Exercise 3: Stack Sorting (using temp Queue) ###############\n");
    readStack(&stack1);

    printf("Stack before sort:\n");
    printStack(stack1);

    sortStackUsingQueue(&stack1);

    printf("Stack after sort:\n");
    printStack(stack1);

    freeStack(&stack1);
}

bool dequeueMin(queue *queue1, queueType *minItem) {
    bool success = FALSE;
    queueType item;
    int queueLength, i;

    if (!isQueueEmpty(queue1)) {
        dequeue(queue1, minItem);
        success = TRUE;

        queueLength = queueSize(queue1);

        for (i = 0; i < queueLength; i++) {
            dequeue(queue1, &item);
            if (item < *minItem) {
                // Push prev item back to the queue
                enqueue(queue1, *minItem);
                *minItem = item;
            } else {
                // Push the item back
                enqueue(queue1, item);
            }
        }
    }

    return success;
}

void sortStackUsingQueue(stack *stack1) {
    int iterations = 0;
    queue queue1;
    stackType item1, minItem;

    if (!isStackEmpty(stack1)) {
        createQueue(&queue1);

        // First, put all elements in the queue. - O(n)
        iterations += stackSize(stack1);
        while (!isStackEmpty(stack1)) {
            stackPop(stack1, &item1); // O(1)
            enqueue(&queue1, item1); // O(1)
        }

        // O(n) to select all elements in queue.
        while (!isQueueEmpty(&queue1)) {
            iterations += queueSize(&queue1);
            dequeueMin(&queue1, &minItem); // O(n): Series
            stackPush(stack1, minItem); // O(1)
        }

        printf("There were %d iterations. Time complexity: O(n^2)\n", iterations);
    }
}

// Ex4
void ex4() {
    stack stack1;

	printf("############### Exercise 4: Stack Sorting (using temp Stack) ###############\n");
	readStack(&stack1);

    printf("Stack before sort:\n");
    printStack(stack1);

    sortStackUsingStack(&stack1);

    printf("Stack after sort:\n");
    printStack(stack1);

	freeStack(&stack1);
}

void sortStackUsingStack(stack *stack1) {
    int iterations = 0;
    stack stack2;
    stackType item1, item2;

    createStackWithInitialCapacity(&stack2, stackSize(stack1));

    // For ascending order, this will make the smallest element to be at the top of stack2. - O(n)
    while (!isStackEmpty(stack1)) {
        iterations++;
        stackPop(stack1, &item1); // O(1)

        // O(n)
        while ((!isStackEmpty(&stack2)) && (stackHead(&stack2, &item2)) && (item2 < item1)) {
            iterations++;
            stackPop(&stack2, &item2); // O(1)
            stackPush(stack1, item2); // O(1)
        }

        stackPush(&stack2, item1); // O(1)
    }

    // Now push all items from second stack to the one we received. This will reverse the order and make the biggest
    // item to be at the top of stack1. - O(n)
    while (!isStackEmpty(&stack2)) {
        iterations++;
        stackPop(&stack2, &item2); // O(1)
        stackPush(stack1, item2); // O(1)
    }

    printf("There were %d iterations. Time complexity: O(n^2)\n", iterations);

    freeStack(&stack2);
}

int readAction() {
	int action;

	printf("Choose an exercise or 0 to exit.\n");
	printf("1. Symmetric Queues\n");
	printf("2. Identical Queues\n");
	printf("3. Stack Sorting (using temp Queue)\n");
	printf("4. Stack Sorting (using temp Stack)\n");
	printf("0. Exit\n");
	scanf_s("%d%*c", &action);

	return action;
}