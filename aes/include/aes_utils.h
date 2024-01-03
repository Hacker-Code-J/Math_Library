#include "aes_config.h"

#ifndef _AES_UTILS_H
#define _AES_UTILS_H

void printU32Array(u32* arr, u32 noElements);

void reverseArray(u8* arr, int i, int j);
void leftRotate(u8* arr, int d, int n);
void rightRotate(u8* arr, int d, int n);

#endif // _AES_UTILS_H