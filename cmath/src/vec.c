#include "vec.h"

const vec VEC_UNDEFINED = {0, NULL};

/**
 * 
*/
vec allocate(u32 dim) {
    vec ret;

    ret.dim = dim;
    ret.elements = (f32*)malloc(dim * sizeof(f32));
    
    return ret;
}

/**
 * 
*/
vec createDefaultVec(u32 dim, f32 val) {
    vec ret = allocate(dim);

    for (u32 i = 0; i < dim; i++)
        ret.elements[i] = val;

    return ret;
}

/**
 * 
*/
vec createEmptyVec(u32 dim) {
    return createDefaultVec(dim, 0.0f);
}

/**
 * 
*/
vec newVec(u32 dim, ...) {
    vec ret = allocate(dim);

    va_list list;
    va_start(list, dim);

    for(u32 i = 0; i < dim; i++)
        ret.elements[i] = va_arg(list, double);
    
    va_end(list);

    return ret;
}

vec copyVec(vec* v) {
    vec ret;
    memcpy(&ret, v, sizeof(vec));
    return ret;
}

void printVec(vec v) {
    printf("[ ");

    for (u32 i = 0; i < v.dim; i++) {
        printf("%f", v.elements[i]);

        if(i < v.dim - 1) printf(", ");
        else printf(" ");
    }

    printf("]\n");
}