#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
vec allocate(u32 dim);

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

vec copyVec(vec* v);

void printVec(vec v);

#endif // _VEC_H