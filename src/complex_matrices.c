#include <math.h>
#include <stdio.h>
#include "complex_matrices.h"

void xiym_set(xiym *m, xiy c, int x, int y) {
    int i = m->cols*y + x;
    m->values[i].x = c.x;
    m->values[i].y = c.y;
}

xiy xiym_get(xiym *m, int x, int y) {
    return m->getter(m, x, y);
}

void xiym_mul_i(xiym *a, xiym *b, xiym *out) {
    // a->rows = b->cols
    int k_max = a->rows;
    for (int row = 0; row < a->rows; row++) {
        for (int col = 0; col < b->cols; col++) {
            xiy res = xiy_zero;
            for (int k = 0; k < k_max; k++) {
                xiy akr = xiym_get(a, k, row);
                xiy bck = xiym_get(b, col, k);
                res = xiy_add(res, xiy_mul(akr, bck));
            }
            xiym_set(out, res, col, row);
        }
    }
}

void xiym_tensor_prod_i(xiym *a, xiym *b, xiym *out) {
    // out->cols = a->cols * b->cols
    // out->rows = a->rows * b->rows
    int ocols = a->cols * b->cols;
    int orows = a->cols * b->cols;
    for (int row = 0; row < orows; row++) {
        for (int col = 0; col < ocols; col++) {
            xiy aval = xiym_get(a, col/b->cols, row/b->rows);
            xiy bval = xiym_get(b, col%b->cols, row%b->rows);
            xiy oval = xiy_mul(aval, bval);
            xiym_set(out, oval, col, row);
        }
    }
}

void xiym_print(xiym *m) {
    printf("xiym:\n");
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->cols; j++) {
            xiy_print(xiym_get(m, j, i));
            printf(" ");
        }
        printf("\n");
    }
}

xiym xiym_identity(int n) {
    xiym In = { n, n, 0, xiym_getter_identity };
    return In;
}

xiy xiym_getter_default(xiym *m, int x, int y) {
    return m->values[y*m->cols + x];
}

xiy xiym_getter_identity(xiym *m, int x, int y) {
    xiy e = { x == y, 0 };
    return e;
}
