#include <stdio.h>

#include "cmath/include/cmath_config.h"
#include "cmath/include/vec.h"
#include "cmath/include/matrix.h"

int main() {
    
    
    
    
    // printf("Hello! %ld\n", sizeof(long double));

    // printf("%ld\n", NUMARGS(int, 3, 4, 5, 6, 34, 45));
    
    
    // vec v = vector(2.0f, -3.0f, 1.0f);
    // vec v2 = createEmptyVec(5);
    // vec v3 = createDefaultVec(3, 2.4f);
    // vec v4 = copyVec(&v3);
    // printVec(v);
    // printVec(v2);
    // printVec(v3);
    // printVec(v4);
    // printf("%d\n",equals(v3, v4));

    // vec v5 = vector(1.0f, 2.0f, -3.0f);
    // vec v6 = scalarMul(v5, 3.0f);
    // printVec(v6);
    // scalarMulBy(&v5, 3.0f);
    // printVec(v5);

    // vec v7 = vector(1.0f, 6.0f, 0.0f);
    // vec v8 = vector(-2.0f, 5.0f, 0.0f);
    // vec v9 = crossProd(v7, v8);
    // printVec(v7);
    // printVec(v8);
    // printVec(v9);

    // mat m = identity(5);
    // mat m2 = zeroMat(5,3);
    // mat m3 = newMat(2, 2, 1.0f, 2.0f, 3.0f, 4.0f);
    // mat m4 = copyMat(m3);
    // printMat(m);
    // printMat(m2);
    // printMat(m3);
    // printMat(m4);
    // printMat(m3);

    // freeMat(&m);
    // freeMat(&m2);
    // freeMat(&m3);

    // vec v = vector(1.02f, 3.141592f, 6.28f);

    // printMat(toRowVec(&v));
    // printMat(toColVec(&v));

    // mat m = newMat(4, 4,
    //     2.0f, -1.0f, 3.0f, 5.0f,
    //     1.0f, -3.0f, 0.0f, 4.0f,
    //     3.0f, 0.0f, -1.0f, -2.0f,
    //     0.0f, 0.0f, 0.0f, 1.0f
    // );
    // printMat(m);
    // printf("\n");
    // vec v = newVec(4,
    //     2.0f, 0.0f, -1.0f, 1.0f
    // );
    // printMat(toColVec(&v));
    // printf("\n");

    // vec res = matVecMul(m, v);
    // printMat(toColVec(&res));

    // mat m1 = matrix(2, 3,
    //     1.0f, 2.0f, 3.0f,
    //     4.0f, 5.0f, 6.0f
    // );
    // printMat(m1); printf("\n");
    // mat m2 = matrix(3, 2,
    //     10.0f, 11.0f,
    //     20.0f, 21.0f,
    //     30.0f, 31.0f
    // );
    // printMat(m2); printf("\n");

    // mat resMat = matMatMul(m1, m2);
    // printMat(resMat);

    // freeMat(&m1);
    // freeMat(&m2);
    // freeMat(&resMat);

    mat m = matrix(4, 4,
        2.0f, -1.0f, 3.0f, 5.0f,
        1.0f, -3.0f, 0.0f, 4.0f,
        3.0f, 0.0f, -1.0f, -2.0f,
        0.0f, 0.0f, 0.0f, 1.0f
    );
    printMat(m);
    printf("\n");
    REF(&m);
    printf("\n");
    printMat(m);
    
    mat m2 = matrix(3,3,
        1.0f, 2.0f, 1.0f,
        0.0f, 1.0f, 2.0f,
        0.0f, 0.0f, 1.0f
    );
    RREF(&m2);
    printf("\n");
    printMat(m2);
    

    return 0;
}