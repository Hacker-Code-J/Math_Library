#include "matrix.h"

const mat MAT_UNDEFINED = {0, 0, NULL};

mat allocateMat(u32 rows, u32 cols) {
    mat ret;

    ret.rows = rows;
    ret.cols = cols;

    ret.elements = (f32**)malloc(rows * sizeof(f32));

    for (u32 i = 0; i < rows; i++)
        ret.elements[i] = (f32*)malloc(cols * sizeof(f32));

    return ret;
}

mat identity(u32 dim) {
    mat ret = allocateMat(dim, dim);

    for (u32 r = 0; r < dim; r++) {
        for (u32 c = 0; c < dim; c++)
            ret.elements[r][c] = (r == c) ? 1.0f : 0.0f;
    }

    return ret;
}

mat zeroMat(u32 rows, u32 cols) {
    mat ret = allocateMat(rows, cols);

    for (u32 r = 0; r < rows; r++) {
        for (u32 c = 0; c < cols; c++)
            ret.elements[r][c] = 0.0f;
    }

    return ret;
}

mat newMat(u32 rows, u32 cols, ...) {
    mat ret = allocateMat(rows, cols);

    va_list list;
    u32 size = rows * cols;
    va_start(list, size);

    for (u32 r = 0; r < rows; r++) {
        for (u32 c = 0; c < cols; c++)
            ret.elements[r][c] = va_arg(list, double);
    }

    va_end(list);

    return ret;
}

mat copyMat(mat m);

mat copyPtrMat(mat* m);

void printMat(mat m) {
    printf("\n");
    for (u32 r = 0; r < m.rows; r++) {
        printf("\n");
        printf("|");

        for (u32 c = 0; c < m.cols; c++)
            printf(" %f", m.elements[r][c]);

        printf("|");
    }
    printf("\n");
}