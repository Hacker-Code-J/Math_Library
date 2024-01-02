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

// mat newMat(u32 rows, u32 cols, ...) {
//     mat ret = allocateMat(rows, cols);

//     va_list list;
//     va_start(list, cols); // 'cols' is the last named argument

//     u32 size = rows * cols; // Calculate the size inside the function
//     for (u32 i = 0; i < size; i++) {
//         u32 r = i / cols;
//         u32 c = i % cols;
//         ret.elements[r][c] = va_arg(list, double);
//     }

//     va_end(list);

//     return ret;
// }

mat newMat(u32 rows, u32 cols, u32 numVals, ...) {
    mat ret = allocateMat(rows, cols);

    va_list list;
    va_start(list, numVals);

    u32 i = 0;

    for (u32 r = 0; r < rows; r++) {
        for (u32 c = 0; c < cols; c++) {
            if(i++ < numVals)
                ret.elements[r][c] = va_arg(list, double);
            else
                ret.elements[r][c] = 0.0f;
        }
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

bool matEquals(mat m1, mat m2) {
    if (m1.rows == m2.rows &&
        m1.cols == m2.cols) {
        for (u32 r = 0; r < m1.rows; r++) {
            for (u32 c = 0; c < m1.cols; c++) {
                if (m1.elements[r][c] != m2.elements[r][c])
                    return false;
            }
        }
        return true;
    }

    return false;
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

mat matScalarSub(mat m, f32 k) {
    mat ret = allocateMat(m.rows, m.cols);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = m.elements[r][c] - k;
    }

    return ret;
}
void matScalarSubFrom(mat* m, f32 k) {
    for (u32 r = 0; r < m->rows; r++) {
        for (u32 c = 0; c < m->cols; c++)
            m->elements[r][c] -= k;
    }
}

mat matScalarMul(mat m, f32 k) {
    mat ret = allocateMat(m.rows, m.cols);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = m.elements[r][c] * k;
    }

    return ret;
}
void matScalarMulBy(mat* m, f32 k) {
    for (u32 r = 0; r < m->rows; r++) {
        for (u32 c = 0; c < m->cols; c++)
            m->elements[r][c] *= k;
    }
}

mat matScalarDiv(mat m, f32 k) {
    mat ret = allocateMat(m.rows, m.cols);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = m.elements[r][c] / k;
    }

    return ret;
}
void matScalarDivBy(mat* m, f32 k) {
    for (u32 r = 0; r < m->rows; r++) {
        for (u32 c = 0; c < m->cols; c++)
            m->elements[r][c] /= k;
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

mat matSub(mat m1, mat m2) {
    if (m1.rows != m2.rows ||
        m1.cols != m2.cols) {
        return MAT_UNDEFINED;
    }

    mat ret = allocateMat(m1.rows, m1.cols);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = m1.elements[r][c] -
                                 m2.elements[r][c];
    }

    return ret;
}
bool matSubFrom(mat* m1, mat m2) {
    if (m1->rows != m2.rows ||
        m1->cols != m2.cols) {
        return false;
    }

    for (u32 r = 0; r < m1->rows; r++) {
        for (u32 c = 0; c < m1->cols; c++)
            m1->elements[r][c] -= m2.elements[r][c];
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

mat transpose(mat* m) {
    mat ret = allocateMat(m->cols, m->rows);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = m->elements[c][r];
    }

    return ret;
}

bool swapRows(mat *m, u32 r1, u32 r2) {
    r1--; r2--;
    if (r1 >= m->rows ||
        r2 >= m->rows ||
        r1 == r2
    ) return false;

    f32* tmp = m->elements[r1];
    m->elements[r1] = m->elements[r2];
    m->elements[r2] = tmp;

    return true;
}
bool addRows(mat* m, u32 r1, u32 r2) {
    r1--; r2--;
    if (r1 >= m->rows ||
        r2 >= m->rows ||
        r1 == r2
    ) return false;

    for (u32 c = 0; c < (m->cols); c++)
        m->elements[r1][c] += m->elements[r2][c];

    return true;
}
bool multiplyRow(mat* m, u32 r, f32 k) {
    r--;

    if (r > (m->rows) ||
        k == 0.0f
    ) return false;

    for (u32 c = 0; c < (m->cols); c++)
        m->elements[r][c] *= k;

    return true;
}
bool addMultiple(mat* m, u32 r1, u32 r2, f32 k) {
    r1--; r2--;

    if (r1 >= (m->rows) ||
        r2 >= (m->rows) ||
        k == 0.0f
    ) return false;

    for (u32 c = 0; c < (m->cols); c++)
        m->elements[r1][c] += (k * m->elements[r2][c]);

    return true;
}

void REF(mat* m) {
    u32 curRow = 0;
    for (u32 c = 0; c < (m->cols); c++) {
        u32 r = curRow;
        if (r >= m->rows) break;

        for (; r < (m->rows); r++) {
            if (m->elements[r][c] != 0.0f) break;
        }

        if (r == m->rows) continue;

        swapRows(m, curRow + 1, r + 1);

        f32 factor = 1 / (m->elements[curRow][c]);
        for (u32 i = c; i < (m->cols); i++)
            m->elements[curRow][i] *= factor;

        for (r = curRow + 1; r < (m->rows); r++)
            addMultiple(m, r+1, curRow, -1 * (m->elements[r][c]));

        curRow++;
    }
}
void RREF(mat* m) {
    u32 curRow = 0;
    for (u32 c = 0; c < (m->cols); c++) {
        u32 r = curRow;
        if (r >= (m->rows)) break;

        for (; r < (m->rows); r++) {
            if (m->elements[r][c] != 0.0f) break;
        }

        if (r == m->rows) continue;

        swapRows(m, curRow + 1, r + 1);

        f32 factor = 1 / (m->elements[curRow][c]);
        for (u32 i = c; i < (m->cols); i++)
            m->elements[curRow][i] *= factor;

        for (r = 0; r < (m->rows); r++) {
            if (r == curRow) continue;
            addMultiple(m, r+1, curRow + 1, -1 * (m->elements[r][c]));
        }

        curRow++;
    }
}

mat augmentVec(mat* m, vec* v) {
    if (m->rows != v->dim) return MAT_UNDEFINED;

    mat ret = allocateMat(m->rows, m->cols + 1);

    for (u32 r = 0; r < m->rows; r++) {
        u32 c = 0;
        for (; c < (m->cols); c++)
            ret.elements[r][c] = m->elements[r][c];
        
        ret.elements[r][c] = v->elements[r];
    }

    return ret;
}
mat augmentMat(mat* m, mat* M) {
    if (m->rows != M->rows) return MAT_UNDEFINED;

    mat ret = allocateMat(m->rows, m->cols + M->cols);

    for (u32 r = 0; r < (m->rows); r++) {
        u32 c = 0;
        for (; c < (m->cols); c++)
            ret.elements[r][c] = m->elements[r][c];

        for (; c < ret.cols; c++)
            ret.elements[r][c] = M->elements[r][c - (m->cols)];
    }

    return ret;
}

mat spliceMat(mat* m, u32 exRow, u32 exCol) {
    exRow--; exCol--;

    mat ret = allocateMat(m->rows - 1, m->cols - 1);

    u32 rowOffset = 0;
    for (u32 r = 0; r < ret.rows; r++) {
        u32 colOffset = 0;

        if (r == exRow) rowOffset++;

        for (u32 c = 0; c < ret.cols; c++) {
            if (c == exCol) colOffset++;

            ret.elements[r][c] = m->elements[r + rowOffset][c + colOffset];
        }

        return ret;
    }
}

f32 cofactor(mat* m, u32 r, u32 c) {
    if (m->rows != m->cols || m->rows == 0) return 0.0f;
    if (r > m->rows || c > m->cols) return 0.0f;

    u8 sgn = ((r + c) & 1) == 0 ? 1: -1;

    mat refineMat = spliceMat(m, r, c);

    f32 ret = sgn;

    freeMat(&refineMat);

    return ret;
}
mat cofactorMat(mat *m) {
    if (m->rows != m->cols || m->rows == 0) return MAT_UNDEFINED;

    mat ret = allocateMat(m->rows, m->cols);

    for (u32 r = 0; r < ret.rows; r++) {
        for (u32 c = 0; c < ret.cols; c++)
            ret.elements[r][c] = cofactor(m, r + 1, c + 1);
    }

    return ret;
}

f32 det(mat* m) {
    if (m->rows != m->cols || m->rows == 0) return 0.0f;

    f32 ret = 0.0f;

    for (u32 c = 0; c < m->cols; c++) {
        if(m->elements[0][c] != 0.0f)
            ret += m->elements[0][c] * cofactor(m, 1, c + 1);
    }

    return ret;
}


f32 mainDetExclusion(mat* m) {
    if (m->rows != m->cols || m->rows == 0) return 0.0f;
    
    u32* skipCols = (u32*)malloc(m->cols * sizeof(u32*));
    u32 noSkipCols = 0;

    f32 ret = subDetExclusion(m, 1, 0, skipCols, &noSkipCols);

    free(skipCols);

    return ret;
}


f32 subDetExclusion(mat* m, u32 row, u32 col, u32* skipCols, u32* noSkipCols) {
    skipCols[*noSkipCols] = col;
    (*noSkipCols)++;

    if (row == m->rows - 1) printf("");

    if (row == m->rows) {
        u32 c = m->cols;

        if (*noSkipCols != 0) {
            if (skipCols[*noSkipCols - 1] != 0) {
                // while (arrCO)
            }
        }
    }
}