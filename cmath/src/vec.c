#include "vec.h"

const vec VEC_UNDEFINED = {0, NULL};

/**
 * 
*/
vec allocateVec(u32 dim) {
    vec ret;

    ret.dim = dim;
    ret.elements = (f32*)malloc(dim * sizeof(f32));
    
    return ret;
}

/**
 * 
*/
vec createDefaultVec(u32 dim, f32 val) {
    vec ret = allocateVec(dim);

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
    vec ret = allocateVec(dim);

    va_list list;
    va_start(list, dim);

    for(u32 i = 0; i < dim; i++)
        ret.elements[i] = va_arg(list, double);
    
    va_end(list);

    return ret;
}

vec copyVec(vec* v) {
    // vec ret;
    // memcpy(&ret, v, sizeof(vec));

    vec ret = allocateVec(v->dim);

    for (u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = v->elements[i];

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

bool equals(vec v1, vec v2) {
    if (v1.dim == v2.dim) {
        for(u32 i = 0; i < v1.dim; i++) {
            if(v1.elements != v2.elements) return false;
        }
        return true;
    }
    return false;
}

vec scalarMul(vec v, f32 k) {
    vec ret = allocateVec(v.dim);

    for(u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = v.elements[i] * k;

    return ret;
}

void scalarMulBy(vec* v, f32 k) {
    for (u32 i = 0; i < v->dim; i++)
        v->elements[i] *= k;
}

vec scalarDiv(vec v, f32 k) {
    vec ret = allocateVec(v.dim);

    for(u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = v.elements[i] / k;

    return ret;
}

void scalarDivBy(vec* v, f32 k) {
    for (u32 i = 0; i < v->dim; i++)
        v->elements[i] /= k;
}

vec power(vec v, f32 k) {
    vec ret = allocateVec(v.dim);

    for (u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = powf(v.elements[i], k);
    
    return ret;
}

void powerOf(vec* v, f32 k) {
    for (u32 i = 0; i < v->dim; i++)
        v->elements[i] = powf(v->elements[i], k);
}

vec add(vec v1, vec v2) {
    if(v1.dim != v2.dim)
        return VEC_UNDEFINED;

    vec ret = allocateVec(v1.dim);

    for (u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = v1.elements[i] + v2.elements[i];

    return ret;
}

bool addTo(vec* v1, vec v2) {
    if (v1->dim != v2.dim)
        return false;

    for (u32 i = 0; i < v1->dim; i++)
        v1->elements[i] += v2.elements[i];

    return true;
}

vec subtract(vec v1, vec v2) {
    if(v1.dim != v2.dim)
        return VEC_UNDEFINED;

    vec ret = allocateVec(v1.dim);

    for (u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = v1.elements[i] - v2.elements[i];

    return ret;
}

bool subtractFrom(vec* v1, vec v2) {
    if (v1->dim != v2.dim)
        return false;

    for (u32 i = 0; i < v1->dim; i++)
        v1->elements[i] -= v2.elements[i];

    return true;
}

vec multiply(vec v1, vec v2) {
    if(v1.dim != v2.dim)
        return VEC_UNDEFINED;

    vec ret = allocateVec(v1.dim);

    for (u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = v1.elements[i] * v2.elements[i];

    return ret;
}

bool multiplyBy(vec* v1, vec v2) {
    if (v1->dim != v2.dim)
        return false;

    for (u32 i = 0; i < v1->dim; i++)
        v1->elements[i] *= v2.elements[i];

    return true;
}

vec divide(vec v1, vec v2) {
    if(v1.dim != v2.dim)
        return VEC_UNDEFINED;

    vec ret = allocateVec(v1.dim);

    for (u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = v1.elements[i] / v2.elements[i];

    return ret;
}

bool divideBy(vec* v1, vec v2) {
    if (v1->dim != v2.dim)
        return false;

    for (u32 i = 0; i < v1->dim; i++)
        v1->elements[i] /= v2.elements[i];

    return true;
}

f32 dotProd(vec v1, vec v2) {
    f32 ret = 0.0f;

    if(v1.dim == v2.dim) {
        for (u32 i = 0; i < v1.dim; i++)
            ret += v1.elements[i] * v2.elements[i];
    }

    return ret;
}

bool orthogonal(vec v1, vec v2) {
    return v1.dim == v2.dim ? dotProd(v1, v2) == 0.0f : false;
}

vec crossProd(vec v1, vec v2) {
    if(v1.dim != 3 || v2.dim != 3) {
        return VEC_UNDEFINED;
    }

    vec ret = allocateVec(3);

    ret.elements[0] = (v1.elements[1] * v2.elements[2]) - (v1.elements[2] * v2.elements[1]);
    ret.elements[1] = -1 * (v1.elements[0] * v2.elements[2]) - (v1.elements[2] * v2.elements[0]);
    ret.elements[2] = (v1.elements[0] * v2.elements[1]) - (v1.elements[1] * v2.elements[0]);

    return ret;
}

f32 magnitude(vec v) {
    return sqrt(magnitudeSquared(v));
}

f32 magnitudeSquared(vec v) {
    f32 ret = 0.0f;

    for (u32 i = 0; i < v.dim; i++)
        ret += v.elements[i] * v.elements[i];
    
    return ret;
}

vec normalized(vec v) {
    vec ret = allocateVec(v.dim);
    f32 mag = magnitude(v);

    for (u32 i = 0; i< v.dim; i++)
        ret.elements[i] /= mag;

    return ret;
}

void normalize(vec* v) {
    f32 mag = magnitude(*v);

    for (u32 i = 0; i < v->dim; i++)
        v->elements[i] /= mag;
}