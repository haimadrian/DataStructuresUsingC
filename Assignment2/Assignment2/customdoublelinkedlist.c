//
// Created by Haim Adrian
//

#include <stdio.h>
#include <stdlib.h>
#include "customdoublelinkedlist.h"

#define TRUE 1
#define FALSE 0

int initLinkedList_custom(doubleLinkedList_custom * list) {
    list->head = list->tail = NULL;
	list->size = 0;

	return TRUE;
}

void freeLinkedList_custom(doubleLinkedList_custom *list, void (*freeItemFunc)(doubleListNodeType_custom)) {
    while (!isLinkedListEmpty_custom(list)) {
        // Remove also free the node.
        removeLast_custom(list, freeItemFunc);
    }
}

doubleListNode_custom *allocNode_d(doubleListNodeType_custom item) {
    doubleListNode_custom *node;
    node = (doubleListNode_custom *)malloc(sizeof(doubleListNode_custom));
    if (node) {
        node->value = item;
        node->next = node->prev = NULL;
    }

    return node;
}

int addFirst_custom(doubleLinkedList_custom * list, doubleListNodeType_custom item) {
	int success = FALSE;
	doubleListNode_custom *node;

	node = allocNode_d(item);

	if (node) {
		success = TRUE;

		if (isLinkedListEmpty_custom(list)) {
			list->tail = node;
		} else {
            list->head->prev = node;
		}

		node->next = list->head;
		list->head = node;
		list->size++;
	}

	return success;
}

int addLast_custom(doubleLinkedList_custom * list, doubleListNodeType_custom item) {
	int success = FALSE;
	doubleListNode_custom *node;

    node = allocNode_d(item);

	if (node) {
		success = TRUE;

		if (isLinkedListEmpty_custom(list)) {
			list->head = node;
		} else {
			list->tail->next = node;
		}

        node->prev = list->tail;
		list->tail = node;
		list->size++;
	}

	return success;
}

int insert_custom(doubleLinkedList_custom * list, doubleListNode_custom *after, doubleListNodeType_custom item) {
	int success = FALSE;
	doubleListNode_custom *node;

	if (!after) {
        success = addFirst_custom(list, item);
	} else {
        node = allocNode_d(item);

        if (node) {
            success = TRUE;

            node->next = after->next;
            node->prev = after;
            after->next = node;

            if (node->next) {
                node->next->prev = node;
            }

            if (list->tail == after) {
                list->tail = node;
            }

            list->size++;
        }
    }

	return success;
}

int insertBefore_custom(doubleLinkedList_custom * list, doubleListNode_custom *before, doubleListNodeType_custom item) {
    int success = FALSE;
    doubleListNode_custom *node;

    if (!before) {
        success = addLast_custom(list, item);
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

            if (list->head == before) {
                list->head = node;
            }

            list->size++;
        }
    }

    return success;
}

int removeFirst_custom(doubleLinkedList_custom * list, void (*freeItemFunc)(doubleListNodeType_custom)) {
	int success = FALSE;
	doubleListNode_custom *node;

	if (!isLinkedListEmpty_custom(list)) {
		success = TRUE;
		node = list->head;
		list->head = node->next;

		// In case of last element.
		if (!list->head) {
			list->tail = NULL;
		} else {
		    list->head->prev = NULL;
		}

		list->size--;

		if (freeItemFunc) {
            freeItemFunc(node->value);
		}

		free(node);
	}

	return success;
}

int removeLast_custom(doubleLinkedList_custom * list, void (*freeItemFunc)(doubleListNodeType_custom)) {
	int success = FALSE;
	doubleListNode_custom *node;

	if (!isLinkedListEmpty_custom(list)) {
		success = TRUE;
		node = list->tail;

		if (list->head == list->tail) {
            list->head = list->tail = NULL;
		} else {
			list->tail = node->prev;
			if (list->tail) {
			    list->tail->next = NULL;
			}
		}

		list->size--;

        if (freeItemFunc) {
            freeItemFunc(node->value);
        }

        free(node);
	}

	return success;
}

int removeFromList_custom(doubleLinkedList_custom * list, doubleListNode_custom *node, void (*freeItemFunc)(doubleListNodeType_custom)) {
	int success = FALSE;
	doubleListNode_custom *nextNode;

	if (node && !isLinkedListEmpty_custom(list)) {
        if (list->head == node) {
            success = removeFirst_custom(list, freeItemFunc);
        } else if (list->tail == node) {
            success = removeLast_custom(list, freeItemFunc);
        } else if (list->size > 1) { // If it is 1 and node differs from head and tail, it is not in list.
            success = TRUE;
            nextNode = node->next;

            if (node->prev) {
                node->prev->next = nextNode;
            }

            if (nextNode) {
                nextNode->prev = node->prev;
            }

            list->size--;

            if (freeItemFunc) {
                freeItemFunc(node->value);
            }

            free(node);
        }
	}

	return success;
}

int head_custom(doubleLinkedList_custom * list, doubleListNode_custom **item) {
	int success = FALSE;

    *item = NULL;
    if (!isLinkedListEmpty_custom(list)) {
        success = TRUE;
        *item = list->head;
    }

	return success;
}

int tail_custom(doubleLinkedList_custom * list, doubleListNode_custom **item) {
	int success = FALSE;

    *item = NULL;
	if (!isLinkedListEmpty_custom(list)) {
        success = TRUE;
        *item = list->tail;
    }

	return success;
}

int isLinkedListEmpty_custom(doubleLinkedList_custom * list) {
	return (list == NULL) || (list->head == NULL);
}

unsigned int linkedListSize_custom(doubleLinkedList_custom * list) {
	return (list == NULL) ? 0 : list->size;
}

doubleListNode_custom *linkedListIterator_custom(doubleLinkedList_custom * list) {
	return (list == NULL) ? NULL : list->head;
}

doubleListNode_custom *linkedListIteratorReversed_custom(doubleLinkedList_custom * list) {
	return (list == NULL) ? NULL : list->tail;
}

int hasNext_custom(doubleListNode_custom *node) {
	return (node != NULL) && (node->next != NULL);
}

int hasPrev_custom(doubleListNode_custom *node) {
    return (node != NULL) && (node->prev != NULL);
}

doubleListNode_custom *next_custom(doubleListNode_custom *node) {
	return (node != NULL ? node->next : NULL);
}

doubleListNode_custom *prev_custom(doubleListNode_custom *node) {
	return (node != NULL ? node->prev : NULL);
}

doubleListNodeType_custom value_custom(doubleListNode_custom *node) {
    return node->value;
}

doubleListNode_custom *findFirst_custom(doubleLinkedList_custom *list, doubleListNodeType_custom item, int (*compareItemsFunc)(doubleListNodeType_custom, doubleListNodeType_custom)) {
	doubleListNode_custom *result = NULL;
	doubleListNode_custom *node;

	for (node = list->head; node != NULL; node = node->next) {
        if (compareItemsFunc(node->value, item)) {
			result = node;
			break;
		}
	}

	return result;
}

doubleListNode_custom *findLast_custom(doubleLinkedList_custom *list, doubleListNodeType_custom item, int (*compareItemsFunc)(doubleListNodeType_custom, doubleListNodeType_custom)) {
    doubleListNode_custom *result = NULL;
    doubleListNode_custom *iter;

    iter = list->tail;
    while (iter != NULL) {
        if (compareItemsFunc(iter->value, item)) {
            result = iter;
            break;
        }

        iter = iter->prev;
    }

    return result;
}

void printLinkedList_custom(doubleLinkedList_custom *list, void (*printItemFunc)(doubleListNodeType_custom)) {
	doubleListNode_custom *node;

	if (!list) {
	    printf("NULL\n");
	} else {
        node = list->head;
        if (node) {
            printf("%c  <-  ", 186); // NULL sign
            printItemFunc(node->value);

            while (node->next != NULL) {
                node = node->next;
                printf("  <-->  ");
                printItemFunc(node->value);
            }
            printf("  ->  %c", 186); // NULL sign
        } else {
            printf("EmptyList");
        }

        printf("  (size=%d)\n", list->size);
    }
}