//
// Created by Haim Adrian
//

#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "doublelinkedlist.h"

#define TRUE 1
#define FALSE 0

int readAction();
void ex1();
void ex2();
void ex3();
void ex4();
void ex5();

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
            case 5: {
                ex5();
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

//////////////////////////////////// EX1 ////////////////////////////////////
int linkedListLengthRec(doubleLinkedList * list) {
    int length = 0;
    doubleListNodeType firstValue;

    if (!isLinkedListEmpty_d(list)) {
        peekFirst_d(list, &firstValue);
        removeFirst_d(list);

        length = 1 + linkedListLengthRec(list);

        // Now add it back.
        addFirst_d(list, firstValue);
    }

    return length;
}

int isPalindrome(doubleLinkedList * list) {
    int result = TRUE;
    doubleListNode *iterator, *reversedIterator;

    iterator = linkedListIterator_d(list);
    reversedIterator = linkedListIteratorReversed_d(list);

    while (result && (iterator != reversedIterator) && (next_d(iterator) != reversedIterator)) {
        result = iterator->value == reversedIterator->value;
        iterator = next_d(iterator);
        reversedIterator = prev_d(reversedIterator);
    }

    if (result && iterator && reversedIterator) {
        // Last comparison in case list size is even.
        result = iterator->value == reversedIterator->value;
    }

    return result;
}

void ex1() {
    doubleLinkedList list;

    printf("\nEX1: Length of a linked list using direct traversing and recursion. We also check if it is a Palindrome.\n");
    if (readLinkedList_d(&list)) {
        printf("List before actions:\n");
        printLinkedList_d(&list);
        printf("List length: %d\n", linkedListSize_d(&list));
        printf("List length using recursion: %d\n", linkedListLengthRec(&list));
        printf("The list is %sa Palindrome.\n", isPalindrome(&list) ? "" : "not ");
        printf("List after actions:\n");
        printLinkedList_d(&list);

        freeLinkedList_d(&list);
    } else {
        printf("Failed to read a linked list.\n");
    }
}

//////////////////////////////////// EX2 ////////////////////////////////////
void ex2() {
    doubleLinkedList list;
    doubleListNodeType inputFirst, inputLast, input, inputAfter;
    doubleListNode *after = NULL;

    printf("\nEX2: Insert into a linked list (After and Last).\n");
    if (readLinkedList_d(&list)) {
        printf("List before actions:\n");
        printLinkedList_d(&list);

        printf("Enter item to insert first:\n");
        scanf_s("%d%*c", &inputFirst);
        addFirst_d(&list, inputFirst);

        printf("Enter item to insert last:\n");
        scanf_s("%d%*c", &inputLast);
        addLast_d(&list, inputLast);

        printf("Enter item to insert somewhere:\n");
        scanf_s("%d%*c", &input);
        printf("After which item should I insert the input?\n");
        scanf_s("%d%*c", &inputAfter);
        after = findFirst_d(&list, inputAfter);

        while (!after) {
            printf("Couldn't find item: %d. Please enter an existing item.\n", inputAfter);
            scanf_s("%d%*c", &inputAfter);
            after = findFirst_d(&list, inputAfter);
        }

        insert_d(&list, after, input);

        printf("List after actions:\n");
        printLinkedList_d(&list);

        freeLinkedList_d(&list);
    } else {
        printf("Failed to read a linked list.\n");
    }
}

//////////////////////////////////// EX3 ////////////////////////////////////
void ex3() {
    linkedList list1;
    doubleLinkedList list2;
    listNodeType input1, inputBefore1;
    doubleListNodeType input2, inputBefore2;
    listNode *before1 = NULL;
    doubleListNode *before2 = NULL;

    printf("\nEX3: Insert before in a linked list (One direction and double direction).\n");
    if (readLinkedList(&list1)) {
        if (readLinkedList_d(&list2)) {
            printf("Lists before actions:\n");
            printLinkedList(&list1);
            printLinkedList_d(&list2);

            printf("Enter item to insert into list1:\n");
            scanf_s("%d%*c", &input1);
            printf("Before which item should I insert the input?\n");
            scanf_s("%d%*c", &inputBefore1);
            before1 = find(&list1, inputBefore1);

            while (!before1) {
                printf("Couldn't find item: %d. Please enter an existing item.\n", inputBefore1);
                scanf_s("%d%*c", &inputBefore1);
                before1 = find(&list1, inputBefore1);
            }

            insertBefore(&list1, before1, input1);


            printf("Enter item to insert into list2:\n");
            scanf_s("%d%*c", &input2);
            printf("Before which item should I insert the input?\n");
            scanf_s("%d%*c", &inputBefore2);
            before2 = findFirst_d(&list2, inputBefore2);

            while (!before2) {
                printf("Couldn't find item: %d. Please enter an existing item.\n", inputBefore2);
                scanf_s("%d%*c", &inputBefore2);
                before2 = findFirst_d(&list2, inputBefore2);
            }

            insertBefore_d(&list2, before2, input2);

            printf("Lists after actions:\n");
            printLinkedList(&list1);
            printLinkedList_d(&list2);

            freeLinkedList(&list1);
            freeLinkedList_d(&list2);
        } else {
            printf("Failed to read a linked list.\n");
        }
    } else {
        printf("Failed to read a linked list.\n");
    }
}

//////////////////////////////////// EX4 ////////////////////////////////////
void ex4() {
    doubleLinkedList list;
    doubleListNode *iterator = NULL;
    int k;

    printf("\nEX4: Insert 0 before every item in a linked list that divides by K.\n");
    if (readLinkedList_d(&list)) {
        printf("List before actions:\n");
        printLinkedList_d(&list);

        printf("Enter K:\n");
        scanf_s("%d%*c", &k);

        for (iterator = linkedListIterator_d(&list); iterator != NULL; iterator = next_d(iterator)) {
            if ((iterator->value % k) == 0) {
                insertBefore_d(&list, iterator, 0);
            }
        }

        printf("List after actions:\n");
        printLinkedList_d(&list);

        freeLinkedList_d(&list);
    } else {
        printf("Failed to read a linked list.\n");
    }
}

//////////////////////////////////// EX5 ////////////////////////////////////
void findMinMax(linkedList *list, listNodeType *min, listNodeType *max) {
    listNode *iterator;

    if (!isLinkedListEmpty(list)) {
        iterator = linkedListIterator(list);

        *min = *max = iterator->value;
        while (hasNext(iterator)) {
            iterator = next(iterator);
            if (iterator->value < *min) {
                *min = iterator->value;
            } else if (iterator->value > *max) {
                *max = iterator->value;
            }
        }
    }
}

void ex5() {
    linkedList list;
    listNode *iterator = NULL, *prevNode = NULL, *temp;
    int min, max, i, arrLength;
    listNodeType *arr;

    printf("\nEX5: Remove duplicated items from linked list.\n");
    if (readLinkedList(&list)) {
        printf("List before actions:\n");
        printLinkedList(&list);

        findMinMax(&list, &min, &max);
        printf("Min=%d, Max=%d\n", min, max);

        if (max == min) {
            // size is retrieved in O(1)
            while (linkedListSize(&list) > 1) {
                // O(1)
                removeFirst(&list);
            }
        } else {
            arrLength = max - min + 1;
            if ((min < 0) || (arrLength > 1000)) {
                printf("Illegal input. List supposed to have natural numbers only. (equivalent to characters)\n");
            } else {
                arr = calloc(arrLength, sizeof(listNodeType));
                if (arr) {
                    for (iterator = linkedListIterator(&list); iterator != NULL;) {
                        i = iterator->value - min;
                        if (arr[i]++) {
                            prevNode->next = iterator->next;
                            temp = iterator;
                            iterator = next(iterator);
                            list.size--;
                            free(temp);

                            if (iterator == NULL) {
                                list.last = prevNode;
                            }
                        } else {
                            prevNode = iterator;
                            iterator = next(iterator);
                        }
                    }

                    free(arr);
                } else {
                    printf("Insufficient memory for array allocation.\n");
                }
            }
        }

        printf("List after actions:\n");
        printLinkedList(&list);

        freeLinkedList(&list);
    } else {
        printf("Failed to read a linked list.\n");
    }
}

int readAction() {
    int action;

    printf("Choose an exercise or 0 to exit.\n");
    printf("1. Linked list length (Direct and Recursion) + Is Palindrome\n");
    printf("2. Insert into linked list\n");
    printf("3. Insert A before B in a linked list\n");
    printf("4. Mark divisor with 0 before in a linked list\n");
    printf("5. Delete duplicate items in a linked list\n");
    printf("0. Exit\n");
    scanf_s("%d%*c", &action);

    return action;
}