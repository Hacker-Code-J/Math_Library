#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "cmath_config.h"
#include "vec.h"

#ifndef _MATRIX_H
#define _MATRIX_H

typedef struct {
    u32 rows;
    u32 cols;
    f32** elements;
} mat;

extern const mat MAT_UNDEFINED;

mat allocateMat(u32 rows, u32 cols);

void freeMat(mat* m);

mat identity(u32 dim);

mat zeroMat(u32 rows, u32 cols);

mat newMat(u32 rows, u32 cols, ...);

mat copyMat(mat m);

mat copyPtrMat(mat* m);

void printMat(mat m);

vec getMatRow(mat* m, u32 row);

vec getMatCol(mat* m, u32 col);

mat toRowVec(vec* v);

mat toColVec(vec* v);

mat matScalarAdd(mat m, f32 k);
void matScalarAddTo(mat* m, f32 k);

mat matAdd(mat m1, mat m2);
bool matAddTo(mat* m1, mat m2);

vec matVecMul(mat m, vec v);

mat matMatMul(mat m1, mat m2);

#endif // _MATRIX_H