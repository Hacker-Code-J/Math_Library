#include <stdio.h>

#include "aes_utils.h"

void printU32Array(u32* arr, u32 noElements) {
    printf("[");
    for (u32 i = 0; i < noElements; i++)
        printf("%u ", arr[i]);
    printf("]\n");
}

void reverseArray(u8* arr, int i, int j) {
    while (i < j) {
        u8 tmp = arr[i];
        arr[i] = arr[j];
        arr[j] = tmp;
        i++; j--;
    }
}

void leftRotate(u8* arr, int d, int n) {
    reverseArray(arr, 0, d - 1);
    reverseArray(arr, d, n - 1);
    reverseArray(arr, 0, n - 1);
}

void rightRotate(u8* arr, int d, int n) {
    leftRotate(arr, n - d, n);
}