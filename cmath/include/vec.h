#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "cmath_config.h"

#ifndef _VEC_H
#define _VEC_H

typedef struct {
    u32 dim;
    f32* elements;
} vec;

extern const vec VEC_UNDEFINED;

/**
 * 
*/
vec allocateVec(u32 dim);

/**
 * 
*/
void freeVec(vec* v);

/**
 * 
*/
vec createDefaultVec(u32 dim, f32 val);

/**
 * 
*/
vec createEmptyVec(u32 dim);

/**
 * 
*/
vec newVec(u32 dim, ...);

/**
 * 
*/
#define vector(...) newVec(NUMARGS(f32, __VA_ARGS__), ##__VA_ARGS__)

/**
 * 
*/
vec copyVec(vec* v);

/**
 * 
*/
void printVec(vec v);

/**
 * 
*/
bool vecEquals(vec v1, vec v2);

/**
 * 
*/
vec vecScalarAdd(vec v, f32 k);

void vecScalarAddTo(vec* v, f32 k);

vec vecScalarSub(vec v, f32 k);

void vecScalarSubFrom(vec* v, f32 k);

vec vecScalarMul(vec v, f32 k);

void vecScalarMulBy(vec* v, f32 k);

vec vecScalarDiv(vec v, f32 k);

void vecScalarDivBy(vec* v, f32 k);

vec vecPower(vec v, f32 k);
void vecPowerOf(vec* v, f32 k);

vec vecAdd(vec v1, vec v2);

bool vecAddTo(vec* v1, vec v2);

vec vecSub(vec v1, vec v2);

bool vecSubFrom(vec* v1, vec v2);

vec vecMul(vec v1, vec v2);

bool vecMulBy(vec* v1, vec v2);

vec vecDiv(vec v1, vec v2);

bool vecDivBy(vec* v1, vec v2);

f32 dotProd(vec v1, vec v2);

bool orthogonal(vec v1, vec v2);

vec crossProd(vec v1, vec v2);

f32 vecMagnitude(vec v);

f32 vecMagnitudeSquared(vec v);

vec vecNormalized(vec v);

void vecNormalize(vec* v);

#endif // _VEC_H