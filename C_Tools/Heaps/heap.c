#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

struct heap {
    int* array;
    int len;
    int max_len;    
    bool (*append)(struct heap* self, int val);
    int (*pop)(struct heap* self);
};

bool heap_insert(struct heap*, int);
int heap_pop(struct heap*);

struct heap* Heap(int max_len) {
    int* array = (int *)malloc(max_len * sizeof(int));
    struct heap* heap = (struct heap*)malloc(sizeof(struct heap));
    heap -> array = array;
    heap -> max_len = max_len;
    heap -> len = 0;
    heap -> append = heap_insert;
    heap -> pop = heap_pop;
    return heap;
}

int heap_parent(int index) {
    return (index - 1) / 2;
}

int heap_left(int index) {
    return 2 * index + 1;
}

int heap_right(int index) {
    return 2 * index + 2;
}

void heap_swap(struct heap* heap, int parent, int index) {
    int temp = heap -> array[index];
    heap -> array[index] = heap -> array[parent];
    heap -> array[parent] = temp;
}

void heap_heapify(struct heap* heap, int index) {
    if (index != 0) {
        int parent = heap_parent(index);
        if (heap -> array[parent] > heap -> array[index]) {
            heap_swap(heap, parent, index);
            heap_heapify(heap, parent);            
        }
    }
}

bool heap_insert(struct heap* heap, int val) {

    if (heap -> len == heap -> max_len) {
        return false;
    }
    heap -> array[heap -> len] = val;
    heap_heapify(heap, heap -> len);
    heap -> len += 1;
    return true;
}

bool heap_has_left(struct heap* heap,int index) {
    return heap_left(index) < heap -> len;
}

bool heap_has_right(struct heap* heap, int index) {
    return heap_right(index) < heap -> len;
}

void heap_heapify_reverse(struct heap* heap, int index) {
    
    int left = heap_left(index);
    int right = heap_right(index);
    int minimum = index;
    if (heap_has_left(heap, index) && (heap -> array[left] < heap -> array[minimum])) {
        minimum = left;
    }
    if (heap_has_right(heap, index) && (heap -> array[right] < heap -> array[minimum])) {
        minimum = right;
    }
    if (minimum != index) {
        heap_swap(heap, index, minimum);
        heap_heapify_reverse(heap, minimum);
    }
}

int heap_pop(struct heap* heap) {
    if (heap -> len == 0) {
        return NULL;
    }   
    int val = heap -> array[0];
    heap -> len -= 1;
    heap -> array[0] = heap -> array[heap -> len];
    if (heap -> len > 1) {
        heap_heapify_reverse(heap, 0);
    }
    return val;
}

void heap_free(struct heap* heap) {
    free(heap -> array);
    free(heap);
}

int main() {

    struct heap* heap = Heap(10);
    int array[10] = {2, 3, 1, 6, 5, 8, -3, -2, 2, 4};
    int arraySize = 10;

    for (int i = 0; i < arraySize; i++) {
        heap -> append(heap, array[i]);
    }

    for (int i = 0; i < arraySize; i++) {
        printf("\n");
        for (int i = 0; i < arraySize; i++) {
            printf("%d, ", heap -> array[i]);
        }
        printf("%d, ", heap -> pop(heap));
    }
    
    
    printf("\n");
}