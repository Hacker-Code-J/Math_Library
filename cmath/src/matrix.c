#include "matrix.h"

const mat MAT_UNDEFINED = {0, 0, NULL};

mat allocateMat(u32 rows, u32 cols) {
    mat ret;

    ret.rows = rows;
    ret.cols = cols;

    ret.elements = (f32**)malloc(rows * sizeof(f32**));

    for (u32 i = 0; i < rows; i++)
        ret.elements[i] = (f32*)malloc(cols * sizeof(f32*));

    return ret;
}

void freeMat(mat* m) {
    free(m->elements);
    m->elements = NULL;
    m->rows = 0;
    m->cols = 0;
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

// mat newMat(u32 rows, u32 cols, ...) {
//     mat ret = allocateMat(rows, cols);

//     va_list list;
//     u32 size = rows * cols;
//     va_start(list, size);

//     for (u32 r = 0; r < rows; r++) {
//         for (u32 c = 0; c < cols; c++)
//             ret.elements[r][c] = va_arg(list, double);
//     }

//     va_end(list);

//     return ret;
// }

mat newMat(u32 rows, u32 cols, ...) {
    mat ret = allocateMat(rows, cols);

    va_list list;
    va_start(list, cols); // 'cols' is the last named argument

    u32 size = rows * cols; // Calculate the size inside the function
    for (u32 i = 0; i < size; i++) {
        u32 r = i / cols;
        u32 c = i % cols;
        ret.elements[r][c] = va_arg(list, double);
    }

    va_end(list);

    return ret;
}

mat copyMat(mat m) {
    return m;
}

mat copyPtrMat(mat* m) {
    mat ret;
    memcpy(&ret, m, sizeof(mat));
    return ret;
}

void printMat(mat m) {
    for (u32 r = 0; r < m.rows; r++) {
        printf("\n");
        printf("|");

        for (u32 c = 0; c < m.cols; c++)
            printf(" %f", m.elements[r][c]);

        printf(" |");
    }
    printf("\n");
}

vec getMatRow(mat* m, u32 row) {
    row--;
    if (row < 0 || row >= m->rows)
        return VEC_UNDEFINED;

    vec ret = allocateVec(m->cols);

    for (u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = m->elements[row][i];

    return ret;
}

vec getMatCol(mat* m, u32 col) {
    col--;
    if (col < 0 || col >= m->cols)
        return VEC_UNDEFINED;

    vec ret = allocateVec(m->rows);

    for (u32 i = 0; i < ret.dim; i++)
        ret.elements[i] = m->elements[i][col];

    return ret;
}

mat toRowVec(vec* v) {
    mat ret = allocateMat(1, v->dim);

    for (u32 i = 0; i < v->dim; i++)
        ret.elements[0][i] = v->elements[i];

    return ret;
}

mat toColVec(vec* v) {
    mat ret = allocateMat(v->dim, 1);

    for (u32 i = 0; i < v->dim; i++)
        ret.elements[i][0] = v->elements[i];

    return ret;
}

mat matScalarAdd(mat m, f32 k) {
    mat ret = allocateMat(m.rows, m.cols);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = m.elements[r][c] + k;
    }

    return ret;
}
void matScalarAddTo(mat* m, f32 k) {
    for (u32 r = 0; r < m->rows; r++) {
        for (u32 c = 0; c < m->cols; c++)
            m->elements[r][c] += k;
    }
}

mat matAdd(mat m1, mat m2) {
    if (m1.rows != m2.rows ||
        m1.cols != m2.cols) {
        return MAT_UNDEFINED;
    }

    mat ret = allocateMat(m1.rows, m1.cols);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = m1.elements[r][c] +
                                 m2.elements[r][c];
    }

    return ret;
}
bool matAddTo(mat* m1, mat m2) {
    if (m1->rows != m2.rows ||
        m1->cols != m2.cols) {
        return false;
    }

    for (u32 r = 0; r < m1->rows; r++) {
        for (u32 c = 0; c < m1->cols; c++)
            m1->elements[r][c] += m2.elements[r][c];
    }

    return true;
}

vec matVecMul(mat m, vec v) {
    if (m.cols != v.dim) return VEC_UNDEFINED;

    vec ret = allocateVec(m.rows);

    for (u32 r = 0; r < ret.dim; r++)
        ret.elements[r] = dotProd(v, getMatRow(&m, r+1));
    
    return ret;
}

mat matMatMul(mat m1, mat m2) {
    if (m1.cols != m2.rows) return MAT_UNDEFINED;

    vec *m1Rows = malloc(m1.rows * sizeof(vec));
    vec *m2Cols = malloc(m2.cols * sizeof(vec));

    for (u32 r = 0; r < m1.rows; r++)
        m1Rows[r] = getMatRow(&m1, r + 1);
    for (u32 c = 0; c < m2.cols; c++)
        m2Cols[c] = getMatCol(&m2, c + 1);

    mat ret = allocateMat(m1.rows, m2.cols);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = dotProd(m1Rows[r], m2Cols[c]);
    }

    for (u32 r = 0; r < m1.rows; r++)
        freeVec(m1Rows + r);
    for (u32 c = 0; c < m2.cols; c++)
        freeVec(m2Cols + c);
    
    free(m1Rows);
    free(m2Cols);

    return ret;
}