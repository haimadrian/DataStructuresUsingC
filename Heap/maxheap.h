//
// Created by Haim Adrian on 10-Sep-19.
//

#ifndef HEAP_MAXHEAP_H
#define HEAP_MAXHEAP_H

typedef int maxHeapType;

typedef struct {
    maxHeapType * elements;
    int length;
    int capacity;
} maxHeap;

int initMaxHeap(maxHeap * heap);
void freeMaxHeap(maxHeap * heap);

// Heapify a sub tree with the root at index 'location'
void maxHeapify(maxHeap * heap, int location);

int parent_max(int location);
int left_max(int location);
int right_max(int location);

int isMaxHeapEmpty(maxHeap * heap);
int maxHeapSize(maxHeap * heap);

maxHeapType extractMax(maxHeap * heap);
maxHeapType getMax(maxHeap * heap);
maxHeapType getValue(maxHeap * heap, int location);
void setValue(maxHeap * heap, int location, maxHeapType value);

void increaseKey_max(maxHeap * heap, int location, int newValue);
void deleteKey_max(maxHeap * heap, int location);
void insertKey_max(maxHeap * heap, maxHeapType key);

void printMaxHeap(maxHeap * heap);

#endif //HEAP_MAXHEAP_H
