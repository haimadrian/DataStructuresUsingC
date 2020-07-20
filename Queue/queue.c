//
// Created by Haim Adrian
//

#include "queue.h"
#include <stdio.h>
#include <math.h>

int createQueue(queue *queue1) {
    queue1->size = 0;
    queue1->head = 0;
    queue1->last = 0;

    return TRUE;
}

int enqueue(queue *queue1, queueType item) {
    int success = FALSE;

    if (!isQueueFull(queue1)) {
        queue1->items[queue1->last] = item;
        queue1->last = (queue1->last + 1) % QUEUE_CAPACITY;
        queue1->size++;
        success = TRUE;
    }

    return success;
}

int dequeue(queue *queue1, queueType *item) {
    int success = FALSE;

    if (queue1->size > 0) {
        *item = queue1->items[queue1->head];
        queue1->head = (queue1->head + 1) % QUEUE_CAPACITY;
        queue1->size--;
        success = TRUE;
    }

    return success;
}

int queueHead(queue *queue1, queueType *item) {
    int success = FALSE;

    if (!isQueueEmpty(queue1)) {
        *item = queue1->items[queue1->head];
        success = TRUE;
    }

    return success;
}

int queueLast(queue *queue1, queueType *item) {
    int success = FALSE;

    if (!isQueueEmpty(queue1)) {
        *item = queue1->items[queue1->last];
        success = TRUE;
    }

    return success;
}

int isQueueEmpty(queue *queue1) {
    return (queue1->size <= 0);
}

int isQueueFull(queue *queue1) {
    return (queue1->size >= QUEUE_CAPACITY);
}

int queueSize(queue *queue1) {
    return queue1->size;
}

/// Prints a queue to console. Example:
/// \code
///  -------------------------------
/// | 3 | 7 | 4 | 8 | 9 | 0 |...|...|  -----  (size=6, capacity=100)
///  -------------------------------
/// \endcode
/// \param queue1 The queue to print
void printQueue(queue queue1) {
    int i, queue1Size, rest;
    queueType item;

    queue1Size = queueSize(&queue1);
    rest = (int)fmin(2, QUEUE_CAPACITY - queue1Size);

    printf(" ---");
    for (i = 1; i < queue1Size + rest; i++) {
        printf("----");
    }
    printf("\n");

    for (i = 0; i < queue1Size; i++) {
        dequeue(&queue1, &item);
        printf("| %c ", item);
    }
    for (i = 0; i < rest; i++) {
         printf("|...");
    }
    printf("|  -----  (size=%d, capacity=%d)\n", queue1Size, QUEUE_CAPACITY);

    printf(" ---");
    for (i = 1; i < queue1Size + rest; i++) {
        printf("----");
    }
    printf("\n");
}