/**
* Assigned By
* -----------
* Name: Haim Adrian
* Group: 61104-61
*
* Name: Shlomki Amir
* Group: 61104-61
*/

#include <stdio.h>
#include "safe.h"
#include "binsearchtree.h"
#include "stack.h"
#include "queue.h"

#define INPUT_BREAK -77999

typedef unsigned int uint;

// Display main menu and return user choose
uint showMainMenu(treeNode_s *tree);

treeNode_s * ex1();

void ex2(treeNode_s * root);

void ex3(treeNode_s * root);

void ex4(treeNode_s ** root);

void fullPrint(treeNode_s * root);

int main() {
    uint action;

    // I would have left this reference as NULL, but we must create an empty tree.
    // So we mark empty tree using the INPUT_BREAK value, which can never exists as we treat
    // it as a null terminator integer.
    treeNode_s *tree = createTree_s(INPUT_BREAK);

    do {
        action = showMainMenu(tree);
        switch (action) {
            case 1: {
                ex4(&tree); // Free previous tree in case there is one
                tree = ex1(); break;
            }
            case 2: ex2(tree); break;
            case 3: ex3(tree); break;
            case 4: ex4(&tree); break;
            case 5: fullPrint(tree); break;
            case 0: /* Do nothing. EXIT */ break;
            default: printf("Unknown action: %d. Please try again.\n", action);
        }
        printf("\n");
    } while (action != 0);

    // Free tree in case there is one
    ex4(&tree);

    printf("Good bye. Press any key to continue...\n");
    getchar();

    return 0;
}

//////////////////// EX1 ////////////////////
treeNode_s * ex1() {
    treeNode_s *root = NULL;
    int input;

    printf("\nPlease enter binary search tree numbers, one by another, or %d to stop:\n", INPUT_BREAK);

    // Get the root and create a new tree out of it.
    input = scanIntSafe();
    if (input == INPUT_BREAK) {
        // Create an empty tree using our wildcard number
        root = createTree_s(INPUT_BREAK);
    } else {
        root = createTree_s(input);

        while ((input = scanIntSafe()) != INPUT_BREAK) {
            // insertTreeNode of binsearchtree.h keeps the binary search tree strategy.
            insertTreeNode_s(root, createTree_s(input));
        }
    }

    return root;
}

//////////////////// EX2 ////////////////////
void ex2(treeNode_s *root) {
    treeNode_s * node = root;
    stack st;

    printf("\nInorder print of input tree:\n");
    if (isTreeEmpty_s(root) || (treeData_s(root) == INPUT_BREAK)) {
        printf("Empty Tree.");
    } else {
        createStack(&st);

        // Push root element so we will base our algorithm on elements in the stack. (as long as it is not empty)
        push(&st, root);

        while (!isStackEmpty(&st)) {
            // Push all leftmost nodes of current node, including current node.
            // We are playing this loop twice:
            // 1. When we first enter the "!isStackEmpty" loop, we scan the leftmost nodes of tree root.
            // 2. Second and later visits are when we went to right tree of current node from previous iteration.
            while ((node = leftTree_s(node))) {
                push(&st, node);
            }

            pop(&st, &node);
            printf("%d ", treeData_s(node));

            // Right plays last.
            if ((node = rightTree_s(node))) {
                push(&st, node);
            }
        }

        freeStack(&st);
    }

    printf("\n");
}

//////////////////// EX3 ////////////////////
void ex3(treeNode_s *root) {
    treeNode_s * node, *temp;
    queue q;

    printf("\nPrint tree by level:\n");
    if (isTreeEmpty_s(root) || (treeData_s(root) == INPUT_BREAK)) {
        printf("Empty Tree.");
    } else {
        createQueue(&q);

        // First enter root node, to base the loop on elements existence
        enqueue(&q, root);

        while (!isQueueEmpty(&q)) {
            dequeue(&q, &node);
            printf("%d ", treeData_s(node));

            // Enqueue left sub node in case there is one
            if ((temp = leftTree_s(node))) {
                enqueue(&q, temp);
            }

            // Enqueue right sub node in case there is one
            if ((temp = rightTree_s(node))) {
                enqueue(&q, temp);
            }
        }

        // Queue is implemented using a fixed array. Hence there is no call to freeQueue procedure.
    }

    printf("\n");
}

//////////////////// EX4 ////////////////////
void ex4(treeNode_s ** root) {
    if (*root) {
        freeTree_s(*root);
        *root = NULL;
    }
}

//////////////////// BONUS ////////////////////
void fullPrint(treeNode_s *root) {
    printf("\nTree:\n");
    if (isTreeEmpty_s(root) || (treeData_s(root) == INPUT_BREAK)) {
        printf("Empty Tree.\n");
    } else {
        // This functionality works on Windows systems only.
        printTree_s(root);
    }
}



//////////////////// COMMON ////////////////////

uint showMainMenu(treeNode_s *tree) {
    printf("Choose an exercise to run or 0 to exit: (There is %s tree in memory)\n", tree == NULL ?
        "no" :
        (treeData_s(tree) == INPUT_BREAK ? "an empty" : "a"));
    printf("1. Enter a new tree%s\n", tree == NULL ? " (Additional actions will be available after entering a tree)" : "");

    if (tree) {
        printf("2. Print inorder\n");
        printf("3. Print levelorder\n");
        printf("4. Clear tree\n");
#ifdef _WIN32
        printf("5. Print tree\n");
#endif
    }

    printf("0. Exit\n");

    return scanUIntSafe();
}