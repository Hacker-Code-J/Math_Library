#include <stdarg.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cmath_config.h"

#ifndef _BIGINT_H
#define _BIGINT_H

typedef struct {
    bool sign;
    int len;
    WORD* val;
} BINT;

typedef struct {
    bool sign;     // true if 0 or positive, false if negative
    u32 capacity;  // number of slots in the array
    u32 used;      // number of used slots in the array
    WORD* digits;  // array of the digits in reverse order; digits[i] = BASE^i component
} bigint;

bigint allocateBigint(u32 capacity);
void freeBigint(bigint* data);

bigint strToBigint(char* str);

bigint newBigint(int data);
bigint newPositiveBigint(u32 data);

char* bigintPtrToString(bigint* data);
char* bigintToString(bigint data);

char compareBigint(bigint data1, bigint data2);

#endif // _BIGINT_H