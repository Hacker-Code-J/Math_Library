#include <stdio.h>

#include "cmath/include/cmath_config.h"
#include "cmath/include/vec.h"
#include "cmath/include/matrix.h"

int main() {
    printf("Hello! %ld\n", sizeof(long double));

    printf("%ld\n", NUMARGS(int, 3, 4, 5, 6, 34, 45));
    
    
    vec v = vector(2.0f, -3.0f, 1.0f);
    vec v2 = createEmptyVec(5);
    vec v3 = createDefaultVec(3, 2.4f);
    vec v4 = copyVec(&v3);
    printVec(v);
    printVec(v2);
    printVec(v3);
    printVec(v4);
    printf("%d\n",equals(v3, v4));

    vec v5 = vector(1.0f, 2.0f, -3.0f);
    vec v6 = scalarMul(v5, 3.0f);
    printVec(v6);
    scalarMulBy(&v5, 3.0f);
    printVec(v5);

    vec v7 = vector(1.0f, 6.0f, 0.0f);
    vec v8 = vector(-2.0f, 5.0f, 0.0f);
    vec v9 = crossProd(v7, v8);
    printVec(v7);
    printVec(v8);
    printVec(v9);

    mat m = identity(5);
    printMat(m);


    return 0;
}