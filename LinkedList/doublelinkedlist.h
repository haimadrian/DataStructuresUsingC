//
// Created by Haim Adrian
//

#ifndef UTILS_DOUBLELINKEDLIST_H
#define UTILS_DOUBLELINKEDLIST_H

//typedef char doubleListNodeType;
typedef int doubleListNodeType;

typedef struct DoubleNode {
	struct DoubleNode *prev;
	struct DoubleNode *next;
    doubleListNodeType value;
} doubleListNode;

typedef struct {
    doubleListNode *first;
    doubleListNode *last;
	unsigned int size;
} doubleLinkedList;

int createLinkedList_d(doubleLinkedList *);

int addFirst_d(doubleLinkedList *, doubleListNodeType);
int addLast_d(doubleLinkedList *, doubleListNodeType);
int insert_d(doubleLinkedList *, doubleListNode *after, doubleListNodeType);
int insertBefore_d(doubleLinkedList *, doubleListNode *before, doubleListNodeType);

int removeFirst_d(doubleLinkedList *);
int removeLast_d(doubleLinkedList *);
int removeFromList_d(doubleLinkedList *, doubleListNode *);

int peekFirst_d(doubleLinkedList *, doubleListNodeType *);
int peekLast_d(doubleLinkedList *, doubleListNodeType *);

int isLinkedListEmpty_d(doubleLinkedList *);

unsigned int linkedListSize_d(doubleLinkedList *);

doubleListNode *linkedListIterator_d(doubleLinkedList *);
doubleListNode *linkedListIteratorReversed_d(doubleLinkedList *);
int hasNext_d(doubleListNode *);
int hasPrev_d(doubleListNode *);
doubleListNode *next_d(doubleListNode *);
doubleListNode *prev_d(doubleListNode *);
doubleListNode *findFirst_d(doubleLinkedList *, doubleListNodeType item);
doubleListNode *findLast_d(doubleLinkedList *, doubleListNodeType item);

void printLinkedList_d(doubleLinkedList *);

int readLinkedList_d(doubleLinkedList *list);

void freeLinkedList_d(doubleLinkedList *list);

#endif //UTILS_DOUBLELINKEDLIST_H
