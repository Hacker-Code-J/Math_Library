#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cmath_config.h"

#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct {
    u32 rows;
    u32 cols;
    f32** elements;
} mat;

extern const mat MAT_UNDEFINED;

mat allocateMat(u32 rows, u32 cols);

mat identity(u32 dim);

mat zeroMat(u32 rows, u32 cols);

mat newMat(u32 rows, u32 cols, ...);

mat copyMat(mat m);

mat copyPtrMat(mat* m);

void printMat(mat m);

#endif // _MATRIX_H