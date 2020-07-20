//
// Created by Haim Adrian on 10-Sep-19.
//

#include <stdio.h>
#include "maxheap.h"

void heapDelete(maxHeap * heap, int i);
void heapIncreaseKey(maxHeap * heap, int i, int k);
int getThirdHighestElement(maxHeap * heap, maxHeapType * value);

int main() {
    maxHeap heap;
    int thirdHighestIndex;
    maxHeapType thirdHighestValue;

    initMaxHeap(&heap);
    insertKey_max(&heap, 7);
    insertKey_max(&heap, 2);
    insertKey_max(&heap, 3);
    insertKey_max(&heap, 6);
    insertKey_max(&heap, 5);
    insertKey_max(&heap, 4);
    insertKey_max(&heap, 1);
    insertKey_max(&heap, 10);
    insertKey_max(&heap, 12);
    insertKey_max(&heap, 14);
    insertKey_max(&heap, 16);
    insertKey_max(&heap, 18);

    printf("Input heap is:\n");
    printMaxHeap(&heap);

    printf("\nDeleting element at index %d\n", 5);
    heapDelete(&heap, 5);
    printf("Updated heap is:\n");
    printMaxHeap(&heap);

    printf("\nIncreasing key at index %d to be %d\n", 3, 17);
    heapIncreaseKey(&heap, 3, 17);
    printf("Updated heap is:\n");
    printMaxHeap(&heap);

    thirdHighestIndex = getThirdHighestElement(&heap, &thirdHighestValue);
    printf("\nThird highest element is at index: %d and its value is: %d\n", thirdHighestIndex, thirdHighestValue);
    printf("Heap is:\n");
    printMaxHeap(&heap);

    freeMaxHeap(&heap);

	printf("\nPress any key to continue...");
	getchar();

    return 0;
}

void heapDelete(maxHeap * heap, int i) {
    deleteKey_max(heap, i); // O(logn)
}

void heapIncreaseKey(maxHeap * heap, int i, int k) {
    increaseKey_max(heap, i, k);
}

int getThirdHighestElement(maxHeap * heap, maxHeapType * value) {
    int left = left_max(0), right = right_max(0), result;

    if (getValue(heap, left) > getValue(heap, right)) {
        result = right;
        *value = getValue(heap, right);
    } else {
        result = left;
        *value = getValue(heap, left);
    }

    return result;
}