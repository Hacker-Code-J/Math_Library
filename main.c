#include <stdio.h>

#include "cmath/include/cmath_config.h"
#include "cmath/include/vec.h"

int main() {
    printf("Hello! %ld\n", sizeof(long double));

    printf("%ld\n", NUMARGS(int, 3, 4, 5, 6, 34, 45));
    
    
    vec v = vector(2.0f, -3.0f, 1.0f);
    printVec(v);

    return 0;
}