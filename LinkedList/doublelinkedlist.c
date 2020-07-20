//
// Created by Haim Adrian
//

#include <stdio.h>
#include <stdlib.h>
#include "doublelinkedlist.h"

#define TRUE 1
#define FALSE 0

int createLinkedList_d(doubleLinkedList * list) {
	list->first = NULL;
	list->last = NULL;
	list->size = 0;

	return TRUE;
}

doubleListNode *allocNode_d(doubleListNodeType item) {
    doubleListNode *node;
    node = malloc(sizeof(doubleListNode));
    if (node) {
        node->value = item;
        node->next = node->prev = NULL;
    }

    return node;
}

int addFirst_d(doubleLinkedList * list, doubleListNodeType item) {
	int success = FALSE;
	doubleListNode *node;

	node = allocNode_d(item);

	if (node) {
		success = TRUE;

		if (isLinkedListEmpty_d(list)) {
			list->last = node;
		} else {
            list->first->prev = node;
		}

		node->next = list->first;
		list->first = node;
		list->size++;
	}

	return success;
}

int addLast_d(doubleLinkedList * list, doubleListNodeType item) {
	int success = FALSE;
	doubleListNode *node;

    node = allocNode_d(item);

	if (node) {
		success = TRUE;

		if (isLinkedListEmpty_d(list)) {
			list->first = node;
		} else {
			list->last->next = node;
		}

        node->prev = list->last;
		list->last = node;
		list->size++;
	}

	return success;
}

int insert_d(doubleLinkedList * list, doubleListNode *after, doubleListNodeType item) {
	int success = FALSE;
	doubleListNode *node;

	if (!after) {
        success = addFirst_d(list, item);
	} else {
        node = allocNode_d(item);

        if (node) {
            success = TRUE;

            node->next = next_d(after);
            node->prev = after;
            after->next = node;

            if (node->next) {
                node->next->prev = node;
            }
            list->size++;
        }
    }

	return success;
}

int insertBefore_d(doubleLinkedList * list, doubleListNode *before, doubleListNodeType item) {
    int success = FALSE;
    doubleListNode *node;

    if (!before) {
        success = addLast_d(list, item);
    } else {
        node = allocNode_d(item);

        if (node) {
            success = TRUE;

            node->next = before;
            node->prev = before->prev;
            before->prev = node;

            if (node->prev) {
                node->prev->next = node;
            }

            list->size++;
        }
    }

    return success;
}

int removeFirst_d(doubleLinkedList * list) {
	int success = FALSE;
	doubleListNode *node;

	if (!isLinkedListEmpty_d(list)) {
		success = TRUE;
		node = list->first;
		list->first = next_d(node);

		// In case of last element.
		if (!list->first) {
			list->last = NULL;
		} else {
		    list->first->prev = NULL;
		}

		list->size--;
		free(node);
	}

	return success;
}

int removeLast_d(doubleLinkedList * list) {
	int success = FALSE;
	doubleListNode *node;

	if (!isLinkedListEmpty_d(list)) {
		success = TRUE;
		node = list->last;

		if (list->first == list->last) {
			list->first = list->last = NULL;
		} else {
			list->last = node->prev;
			if (list->last) {
			    list->last->next = NULL;
			}
		}

		list->size--;
		free(node);
	}

	return success;
}

int removeFromList_d(doubleLinkedList * list, doubleListNode *node) {
	int success = FALSE;
	doubleListNode *nextNode;

	if (!isLinkedListEmpty_d(list)) {
        success = TRUE;

		if ((list->first == list->last) && (list->first == node)) {
			list->first = list->last = NULL;
		} else {
            nextNode = next_d(node);
            node->prev->next = nextNode;

			if (nextNode) {
			    nextNode->prev = node->prev;
			}
		}

        list->size--;
        free(node);
	}

	return success;
}

int peekFirst_d(doubleLinkedList * list, doubleListNodeType *item) {
	int success = FALSE;

	if (!isLinkedListEmpty_d(list)) {
		*item = list->first->value;
	}

	return success;
}

int peekLast_d(doubleLinkedList * list, doubleListNodeType *item) {
	int success = FALSE;

	if (!isLinkedListEmpty_d(list)) {
		*item = list->last->value;
	}

	return success;
}

int isLinkedListEmpty_d(doubleLinkedList * list) {
	return list->size == 0;
}

unsigned int linkedListSize_d(doubleLinkedList * list) {
	return list->size;
}

doubleListNode *linkedListIterator_d(doubleLinkedList * list) {
	return list->first;
}

doubleListNode *linkedListIteratorReversed_d(doubleLinkedList * list) {
	return list->last;
}

int hasNext_d(doubleListNode *node) {
	return (node != NULL) && (next_d(node) != NULL);
}

int hasPrev_d(doubleListNode *node) {
    return (node != NULL) && (prev_d(node) != NULL);
}

doubleListNode *next_d(doubleListNode *node) {
	return (node != NULL ? node->next : NULL);
}

doubleListNode *prev_d(doubleListNode *node) {
	return (node != NULL ? node->prev : NULL);
}

doubleListNode *findFirst_d(doubleLinkedList *list, doubleListNodeType item) {
	doubleListNode *result = NULL;
	doubleListNode *node;

	for (node = linkedListIterator_d(list); node != NULL; node = next_d(node)) {
		if (node->value == item) {
			result = node;
			break;
		}
	}

	return result;
}

doubleListNode *findLast_d(doubleLinkedList *list, doubleListNodeType item) {
    doubleListNode *result = NULL;
    doubleListNode *node;

    node = linkedListIteratorReversed_d(list);
    while (hasPrev_d(node)) {
        if (node->value == item) {
            result = node;
            break;
        }

        node = prev_d(node);
    }

    return result;
}

void printLinkedList_d(doubleLinkedList *list) {
	int isCharList;
	doubleListNode *node;

	isCharList = (sizeof(doubleListNodeType) == sizeof(char));

	node = linkedListIterator_d(list);
	if (node) {
		if (isCharList) {
			printf("%c", node->value);
		} else {
			printf("%c  <-  %d", 186, node->value);
		}
	}

	while (hasNext_d(node)) {
		node = next_d(node);

		if (isCharList) {
			printf("  <-->  %c", node->value);
		} else {
			printf("  <-->  %d", node->value);
		}
	}
	printf("  ->  %c", 186); // NULL sign

	printf("  (size=%d)\n", linkedListSize_d(list));
}

int readLinkedList_d(doubleLinkedList *list) {
	unsigned int n;
	int success, isCharQueue;
	doubleListNodeType item;

	isCharQueue = (sizeof(doubleListNodeType) == sizeof(char));
	success = createLinkedList_d(list);

	if (success) {
		printf("Enter amount of %s to scan into linked list:\n", isCharQueue ? "characters" : "numbers");
		scanf_s("%d%*c", &n);

		printf("Enter %d items:\n", n);
		while (n-- > 0) {
			if (isCharQueue) {
				scanf_s("%c%*c", &item, sizeof(doubleListNodeType));
			} else {
				scanf_s("%d%*c", &item);
			}
			addLast_d(list, item);
		}
	}

	return success;
}

void freeLinkedList_d(doubleLinkedList *list) {
	while (!isLinkedListEmpty_d(list)) {
		// Remove also free the node.
		removeLast_d(list);
	}
}