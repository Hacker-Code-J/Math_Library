#include "cmath_config.h"

void swap(u32* a, u32* b) {
    *a ^= *b;
    *b ^= *a ^ *b;
    *a ^= *b;
}
void swapFloat(f32* a, f32* b) {
    swap((u32*)a, (u32*)b);
}