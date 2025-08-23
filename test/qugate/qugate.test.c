#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../src/qugate/qugate.h"

#define EPSILON 1e-9

typedef void (*mat_func)(xiy *);

int xiy_equals(xiy a, xiy b) {
    return labs(a.x - b.x) < EPSILON && labs(a.y - b.y) < EPSILON;
}

void xiy_print_2x2(xiy *mat) {
    printf("  {{%lf,%lf},{%lf,%lf},\n", mat[0].x, mat[0].y, mat[1].x, mat[1].y);
    printf("   {%lf,%lf},{%lf,%lf}}\n", mat[2].x, mat[2].y, mat[3].x, mat[3].y);
}

// TODO(): Make qugate test more robust
int main(int argc, char *argv[]) {
    xiy inv_sqrt2 = xiy_mul_s(xiy_one, 1/sqrt(2));
    xiy mat_empty_2x2[4] = { xiy_zero, xiy_zero, xiy_zero, xiy_zero };
    xiy mat_i[4] = { xiy_one, xiy_zero, xiy_zero, xiy_one };
    xiy mat_x[4] = { xiy_zero, xiy_one, xiy_one, xiy_zero };
    xiy mat_y[4] = { xiy_zero, xiy_mul_s(xiy_i, -1), xiy_i, xiy_zero };
    xiy mat_z[4] = { xiy_one, xiy_zero, xiy_zero, xiy_mul_s(xiy_one, -1) };
    xiy mat_h[4] = { inv_sqrt2, inv_sqrt2, inv_sqrt2, xiy_mul_s(inv_sqrt2, -1) };

    xiy mat_cx[16] = {
        xiy_one, xiy_zero, xiy_zero, xiy_zero,
        xiy_zero, xiy_one, xiy_zero, xiy_zero,
        xiy_zero, xiy_zero, xiy_zero, xiy_one,
        xiy_zero, xiy_zero, xiy_one, xiy_zero
    };
    xiy mat_cz[16] = {
        xiy_one, xiy_zero, xiy_zero, xiy_zero,
        xiy_zero, xiy_one, xiy_zero, xiy_zero,
        xiy_zero, xiy_zero, xiy_one, xiy_zero,
        xiy_zero, xiy_zero, xiy_zero, xiy_mul_s(xiy_one, -1)
    };

    xiy *mat_2x2s[5] = {
        mat_i,
        mat_x,
        mat_y,
        mat_z,
        mat_h
    };

    mat_func mat_funcs[5] = {
        qugate_i,
        qugate_x,
        qugate_y,
        qugate_z,
        qugate_h
    };

    for (int i = 0; i < 5; i++) {
        xiy *mat = mat_2x2s[i];
        mat_func qugate = mat_funcs[i];
        qugate(mat_empty_2x2);
        for (int j = 0; j < 4; j++) {
            if (!xiy_equals(mat_empty_2x2[j], mat[j])) {
                printf("TEST -- qugate -- FAILED -- qugate comparison %i: Expected qugate to be\n");
                xiy_print_2x2(mat);
                printf("  but got\n");
                xiy_print_2x2(mat_empty_2x2);
                exit(0);
            }
        }
    }

    printf("TEST -- qugate -- SUCCESS\n");
}
