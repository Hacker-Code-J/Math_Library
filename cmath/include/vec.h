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
bool equals(vec v1, vec v2);

/**
 * 
*/
vec scalarMul(vec v, f32 k);

void scalarMulBy(vec* v, f32 k);

vec scalarDiv(vec v, f32 k);

void scalarDivBy(vec* v, f32 k);

vec power(vec v, f32 k);
void powerOf(vec* v, f32 k);

vec add(vec v1, vec v2);

bool addTo(vec* v1, vec v2);

vec subtract(vec v1, vec v2);

bool subtractFrom(vec* v1, vec v2);

vec multiply(vec v1, vec v2);

bool multiplyBy(vec* v1, vec v2);

vec divide(vec v1, vec v2);

bool divideBy(vec* v1, vec v2);

f32 dotProd(vec v1, vec v2);

bool orthogonal(vec v1, vec v2);

vec crossProd(vec v1, vec v2);

f32 magnitude(vec v);

f32 magnitudeSquared(vec v);

vec normalized(vec v);

void normalize(vec* v);

#endif // _VEC_H