#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define min(a,b) (((a) < (b)) ? (a) : (b))

void stdout_array(int** array, int arraySize, int* columnSizes) {
    printf("[ ");
    for (int i = 0; i < arraySize; i++) {
        printf("[");
        for (int j = 0; j < columnSizes[i]; j++) {
            printf("%d", array[i][j]);
            if (j < columnSizes[i] - 1) { printf(", "); }
        }
        printf("]");
        if (i < arraySize - 1) { printf(", "); }
    }
    printf("]");
}

bool cmp_less_than(int* array1, int array1Size, int* array2, int array2Size) {

    int i = 0;
    int min_size = min(array1Size, array2Size);

    while ((i < min_size) && (array1[i] == array2[i])) { i += 1; }
    if (i == min_size) {return false;}
    else if (array1[i] < array2[i]) {return true;}
    else if (array1[i] > array2[i]) {return false;}
    else if (array1Size < array2Size) {return true;}
    return false;

}


void merge(int left, int mid, int right, int** array, int** sortedArray, int* columnSizes) {
    
    int i = left;
    int j = mid;

    for (int k = left; k < right; k++) {
        if ((i < mid) && (j < right)) {
            if (cmp_less_than(array[i], columnSizes[i], array[j], columnSizes[j])) {
                sortedArray[k] = array[i];
                i++;
            } else {
                sortedArray[k] = array[j];
                j++;
            }  
            
        } else if (i < mid) {
            sortedArray[k] = array[i];
            i++;
        } else {
            sortedArray[k] = array[j];
            j++;
        }
    }
    
    for (int k = left; k < right; k++) {
        array[k] = sortedArray[k];
    }
}

void mergeSort(int left, int right, int** array, int** sortedArray, int* columnSizes) {

    if (left == (right - 1)) {
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(left, mid, array, sortedArray, columnSizes);
    mergeSort(mid, right, array, sortedArray, columnSizes);
    merge(left, mid, right, array, sortedArray, columnSizes);
}


int main() {
    
    int arraySize = 0;
    int** array;
    int* columnSizes;

    printf("enter the array size: ");
    scanf("%d", &arraySize);

    array = (int**)malloc(sizeof(int*) * arraySize);
    columnSizes = (int*)malloc(sizeof(int) * arraySize);
    for (int i = 0; i < arraySize; i++) {
        printf("enter %dth column size : ", i);
        scanf("%d", &columnSizes[i]);
        array[i] = (int*)malloc(sizeof(int) * columnSizes[i]);
        printf("enter the %dth array elements : ", i);
        for (int j = 0; j < columnSizes[i]; j++) {
            scanf("%d", &array[i][j]);
        }
        printf("\n");
    }
    

    stdout_array(array, arraySize, columnSizes);
    printf("\n");

    int** sortedArray = (int**)malloc(sizeof(int*) * arraySize);

    mergeSort(0, arraySize, array, sortedArray, columnSizes);

    stdout_array(array, arraySize, columnSizes);
    return 0;

}