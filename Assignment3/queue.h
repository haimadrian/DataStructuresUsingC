//
// Created by Haim Adrian
//

#ifndef UTILS_QUEUE_H
#define UTILS_QUEUE_H

#include "binsearchtree.h"

#define TRUE 1
#define FALSE 0
#define QUEUE_CAPACITY 100

typedef treeNode_s * queueType;

typedef struct {
    int head, last, size;

    // Array with constant capacity to hold elements in the queue. We use a constant array for maximum performance O(1)
    // when reading and writing elements to the queue. (In order to avoid of shifting elements)
    queueType items[QUEUE_CAPACITY];
} queue;

int createQueue(queue *);

int enqueue(queue *, queueType);

int dequeue(queue *, queueType *);

int queueHead(queue *, queueType *);

int queueLast(queue *, queueType *);

int isQueueEmpty(queue *);

int isQueueFull(queue *);

int queueSize(queue *);

void printQueue(queue);

#endif //UTILS_QUEUE_H
