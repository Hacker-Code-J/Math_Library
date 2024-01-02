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

mat newMat(u32 rows, u32 cols, u32 numVals, ...);

#define matrix(rows, cols, ...) newMat(rows, cols, NUMARGS(f32, __VA_ARGS__), ##__VA_ARGS__)

mat copyMat(mat m);

mat copyPtrMat(mat* m);

void printMat(mat m);

vec getMatRow(mat* m, u32 row);

vec getMatCol(mat* m, u32 col);

mat toRowVec(vec* v);

mat toColVec(vec* v);

bool matEquals(mat m1, mat m2);

mat matScalarAdd(mat m, f32 k);
void matScalarAddTo(mat* m, f32 k);

mat matScalarSub(mat m, f32 k);
void matScalarSubFrom(mat* m, f32 k);

mat matScalarMul(mat m, f32 k);
void matScalarMulBy(mat* m, f32 k);

mat matScalarDiv(mat m, f32 k);
void matScalarDivBy(mat* m, f32 k);

mat matAdd(mat m1, mat m2);
bool matAddTo(mat* m1, mat m2);

mat matSub(mat m1, mat m2);
bool matSubFrom(mat* m1, mat m2);

vec matVecMul(mat m, vec v);

mat matMatMul(mat m1, mat m2);

mat transpose(mat* m);

bool swapRows(mat *m, u32 r1, u32 r2);
bool addRows(mat* m, u32 r1, u32 r2);
bool multiplyRow(mat* m, u32 r, f32 k);
bool addMultiple(mat* m, u32 r1, u32 r2, f32 k);

void REF(mat* m);
void RREF(mat* m);

mat augmentVec(mat* m, vec* v);
mat augmentMat(mat* m, mat* M);

mat spliceMat(mat* m, u32 exRow, u32 exCol);

f32 cofactor(mat* m, u32 r, u32 c);
mat cofactorMat(mat *m);

f32 det(mat* m);
f32 mainDetExclusion(mat* m);
f32 subDetExclusion(mat* m, u32 row, u32 col, u32* skipCols, u32* noSkipCols);

#endif // _MATRIX_H