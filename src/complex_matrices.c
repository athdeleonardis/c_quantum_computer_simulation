#include <math.h>
#include "complex_matrices.h"

void xiym_set(xiym *m, xiy c, int x, int y) {
    m->values[m->length*y + x] = c;
}

xiy xiym_get(xiym *m, int x, int y) {
    return m->getter(m, x, y);
}

void xiym_mul_i(xiym *a, xiym *b, xiym *out) {
    for (int row = 0; row < out->length; row++) {
        for (int col = 0; col < out->length; col++) {
            xiy res = xiy_zero;
            for (int k = 0; k < out->length; k++) {
                xiy ark = xiym_get(a, k, row);
                xiy bkc = xiym_get(b, col, k);
                res = xiy_add(res, xiy_mul(ark, bkc));
            }
            xiym_set(out, res, col, row);
        }
    }
}

xiym xiym_identity(int n) {
    xiym In = { n, 0, xiy_matrix_getter_identity };
    return In;
}

xiy xiy_matrix_getter_default(xiym *m, int x, int y) {
    return m->values[y*m->length + x];
}

xiy xiy_matrix_getter_identity(xiym *m, int x, int y) {
    xiy e = { x == y, 0 };
    return e;
}

