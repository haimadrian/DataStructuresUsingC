//
// Created by Haim Adrian on 10-Sep-19.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "maxheap.h"

#define STARTING_CAPACITY 16
#define WIDTH 10
#define TRUE 1
#define FALSE 0

int initMaxHeap(maxHeap * heap) {
    int success = FALSE;

    if (!heap) {
        printf("Cannot initialize a NULL heap. You must allocate a heap first.\n");
    } else {
        heap->elements = (maxHeapType *) calloc(STARTING_CAPACITY, sizeof(maxHeapType));

        if (heap->elements) {
            success = TRUE;
            heap->capacity = STARTING_CAPACITY;
            heap->length = 0;
        }
    }

    return success;
}

void freeMaxHeap(maxHeap * heap) {
    if (heap && heap->elements) {
        free(heap->elements);
        heap->elements = NULL;
        heap->length = -1;
        heap->capacity = 0;
    }
}

void swap(maxHeapType * a, maxHeapType *b) {
    maxHeapType temp = *a;
    *a = *b;
    *b = temp;
}

// Heapify a sub tree with the root at index 'location'
void maxHeapify(maxHeap * heap, int location) {
    int left = left_max(location), right = right_max(location), max = location;

    if ((left < heap->length) && (heap->elements[left] > heap->elements[max])) {
        max = left;
    }

    if ((right < heap->length) && (heap->elements[right] > heap->elements[max])) {
        max = right;
    }

    // Breaks recursion, no need to swap if location is already the minimum between itself and its two children.
    if (max != location) {
        swap(&(heap->elements[location]), &(heap->elements[max]));
        maxHeapify(heap, max);
    }
}

int parent_max(int location) {
    return (location - 1) / 2;
}

int left_max(int location) {
    return (location * 2) + 1;
}

int right_max(int location) {
    return (location * 2) + 2;
}

int isMaxHeapEmpty(maxHeap * heap) {
    return (heap == NULL) || (heap->length <= 0);
}

int maxHeapSize(maxHeap * heap) {
    return heap ? heap->length : 0;
}

maxHeapType extractMax(maxHeap * heap) {
    maxHeapType max = heap->elements[0];
    (heap->length)--;

    if (heap->length > 0) {
        heap->elements[0] = heap->elements[heap->length];
        maxHeapify(heap, 0);
    } else {
        heap->elements[0] = 0;
    }

    return max;
}

maxHeapType getMax(maxHeap * heap) {
    return heap->elements[0];
}

maxHeapType getValue(maxHeap * heap, int location) {
    return heap->elements[location];
}

void setValue(maxHeap * heap, int location, maxHeapType value) {
    heap->elements[location] = value;
}

void increaseKey_max(maxHeap * heap, int location, int newValue) {
    maxHeapType parent;

    if (newValue > heap->elements[location]) {
        heap->elements[location] = newValue;

        // Now make sure the element is at its position. (O(logn) max)
        while (((parent = parent_max(location)) >= 0) && (heap->elements[location] > heap->elements[parent])) {
            swap(&(heap->elements[location]), &(heap->elements[parent]));
            location = parent;
        }
    }
}

void deleteKey_max(maxHeap * heap, int location) {
    if (location == 0) {
        extractMax(heap);
    } else {
        increaseKey_max(heap, location, INT_MAX);
        extractMax(heap);
    }
}

void insertKey_max(maxHeap * heap, maxHeapType key) {
    int parent, keyIndex;

    if (heap) {
        // Check if need to enlarge heap size
        if (heap->length == heap->capacity) {
            heap->capacity = (int)(heap->capacity * 1.75);
            heap->elements = (maxHeapType *) _recalloc(heap->elements, heap->capacity, sizeof(maxHeapType));
        }

        keyIndex = heap->length;
        heap->elements[(heap->length)++] = key;

        // Now make sure the last added element is at its position. (O(logn) max)
        while (((parent = parent_max(keyIndex)) >= 0) && (heap->elements[keyIndex] > heap->elements[parent])) {
            swap(&(heap->elements[keyIndex]), &(heap->elements[parent]));
            keyIndex = parent;
        }
    }
}

int countDigits(int number) {
    int digits = 1;

    number = abs(number);
    while ((number = number / 10) > 0) {
        digits++;
    }

    return digits;
}

void printMaxHeap(maxHeap * heap) {
    int heapHeight, potentialAmountOfElementsAtLastLevel, itemWidth, i, rowWidth, level, from, to, temp, nodeArea, amountOfNodesInLevel;

    if (!heap) {
        printf("NULL\n");
    } else if (heap->length == 1) {
        printf("%d\n", heap->elements[0]);
    } else {
        heapHeight = (int)logb(heap->length);
        potentialAmountOfElementsAtLastLevel = (int)pow(2, heapHeight);
        rowWidth = potentialAmountOfElementsAtLastLevel * WIDTH;

        //printf("heapHeight=%d, potentialAmountOfElementsAtLastLevel=%d, rowWidth=%d\n", heapHeight, potentialAmountOfElementsAtLastLevel, rowWidth);
        itemWidth = countDigits(heap->elements[0]);
        nodeArea = rowWidth;
        printf("%*s %-*d\n", (nodeArea / 2) - (itemWidth / 2), " ", WIDTH - 2, heap->elements[0]);
        to = 0;
        amountOfNodesInLevel = 1;
        for (level = 0; level < heapHeight; level++) {
            from = to + 1;
            to = from * 2;
            amountOfNodesInLevel *= 2;
            nodeArea = rowWidth / amountOfNodesInLevel;
            for (i = from; i <= to && i < heap->length; i++) {
                itemWidth = countDigits(heap->elements[i]);
                temp = (nodeArea / 2) - (itemWidth / 2);
                printf("%*s%-*d%*s", temp, " ", itemWidth, heap->elements[i], (itemWidth % 2 ? temp - 1 : temp), " ");
            }
            printf("\n");
        }
    }
}