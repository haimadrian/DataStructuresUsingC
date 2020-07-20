//
// Created by Haim Adrian
//

#ifndef ASSIGNMENT2_CUSTOMDOUBLELINKEDLIST_H
#define ASSIGNMENT2_CUSTOMDOUBLELINKEDLIST_H

#include "polynomialtype.h"

#ifndef CUSTOM_LIST_NODE_TYPE
#define CUSTOM_LIST_NODE_TYPE
typedef polynomialNodeType * doubleListNodeType_custom;
#endif

typedef struct doubleListNode_custom {
	struct doubleListNode_custom *prev;
	struct doubleListNode_custom *next;
    doubleListNodeType_custom value;
} doubleListNode_custom;

typedef struct {
    doubleListNode_custom *head;
    doubleListNode_custom *tail;
	unsigned int size;
} doubleLinkedList_custom;

int initLinkedList_custom(doubleLinkedList_custom *list);
void freeLinkedList_custom(doubleLinkedList_custom *list, void (*freeItemFunc)(doubleListNodeType_custom));

int addFirst_custom(doubleLinkedList_custom *list, doubleListNodeType_custom item);
int addLast_custom(doubleLinkedList_custom *list, doubleListNodeType_custom item);
int insert_custom(doubleLinkedList_custom *list, doubleListNode_custom *after, doubleListNodeType_custom item);
int insertBefore_custom(doubleLinkedList_custom *list, doubleListNode_custom *before, doubleListNodeType_custom item);

int removeFirst_custom(doubleLinkedList_custom *list, void (*freeItemFunc)(doubleListNodeType_custom));
int removeLast_custom(doubleLinkedList_custom *list, void (*freeItemFunc)(doubleListNodeType_custom));
int removeFromList_custom(doubleLinkedList_custom *list, doubleListNode_custom *node, void (*freeItemFunc)(doubleListNodeType_custom));

int head_custom(doubleLinkedList_custom *list, doubleListNode_custom ** item);
int tail_custom(doubleLinkedList_custom *list, doubleListNode_custom ** item);

int isLinkedListEmpty_custom(doubleLinkedList_custom *list);

unsigned int linkedListSize_custom(doubleLinkedList_custom *list);

doubleListNode_custom *linkedListIterator_custom(doubleLinkedList_custom *list);
doubleListNode_custom *linkedListIteratorReversed_custom(doubleLinkedList_custom *list);
int hasNext_custom(doubleListNode_custom *node);
int hasPrev_custom(doubleListNode_custom *node);
doubleListNode_custom *next_custom(doubleListNode_custom *node);
doubleListNode_custom *prev_custom(doubleListNode_custom *node);
doubleListNodeType_custom value_custom(doubleListNode_custom *node);
doubleListNode_custom *findFirst_custom(doubleLinkedList_custom *list, doubleListNodeType_custom item, int (*compareItemsFunc)(doubleListNodeType_custom, doubleListNodeType_custom));
doubleListNode_custom *findLast_custom(doubleLinkedList_custom *list, doubleListNodeType_custom item, int (*compareItemsFunc)(doubleListNodeType_custom, doubleListNodeType_custom));

void printLinkedList_custom(doubleLinkedList_custom *list, void (*printItemFunc)(doubleListNodeType_custom));

#endif //ASSIGNMENT2_CUSTOMDOUBLELINKEDLIST_H
