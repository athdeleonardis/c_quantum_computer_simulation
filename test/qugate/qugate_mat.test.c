#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../src/qugate/qugate_mat.h"

#define N_TESTS_2X2 5
#define N_TESTS_4X4 3
#define ERROR_VALUE 133
#define EPSILON 1e-9

typedef void (*mat_func)(xiy *);

int xiy_equals(xiy a, xiy b) {
    return fabs(a.x - b.x) < EPSILON && fabs(a.y - b.y) < EPSILON;
}

void xiy_print_2x2(xiy *mat) {
    printf("{{%lf,%lf},{%lf,%lf},\n", mat[0].x, mat[0].y, mat[1].x, mat[1].y);
    printf(" {%lf,%lf},{%lf,%lf}}\n", mat[2].x, mat[2].y, mat[3].x, mat[3].y);
}

void xiy_print_4x4(xiy *mat) {
    printf("Matrix:\n");
    for (int i = 0; i < 16; i += 4) {
        if (i == 0)
            printf("{");
        else
            printf(" ");
        printf("{%lf,%lf},{%lf,%lf},{%lf,%lf},{%lf,%lf}", mat[i+0].x, mat[i+0].y, mat[i+1].x, mat[i+1].y, mat[i+2].x, mat[i+2].y, mat[i+3].x, mat[i+3].y);
        if (i == 12)
            printf("}\n");
        else
            printf(",\n");
    }
}

typedef struct test {
    mat_func func;
    xiy *output;
} test_t;

void _qugate_mat_ch(xiy *mat_4x4) {
    xiy mat_h[4];
    qugate_mat_h(mat_h);
    qugate_mat_cu(mat_4x4, mat_h);
}

void qugate_mat_error(xiy *mat_4x4) {
    for (int i = 0; i < 16; i++) {
        mat_4x4[i] = xiy_mul_s(xiy_one, ERROR_VALUE);
    }
}

// TODO(): Make qugate test more robust
int main(int argc, char *argv[]) {
    xiy inv_sqrt2 = xiy_mul_s(xiy_one, M_SQRT1_2);
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
    xiy mat_ch[16] = {
        xiy_one, xiy_zero, xiy_zero, xiy_zero,
        xiy_zero, xiy_one, xiy_zero, xiy_zero,
        xiy_zero, xiy_zero, inv_sqrt2, inv_sqrt2,
        xiy_zero, xiy_zero, inv_sqrt2, xiy_mul_s(inv_sqrt2, -1)
    };

    test_t test_i = { qugate_mat_i, mat_i };
    test_t test_x = { qugate_mat_x, mat_x };
    test_t test_y = { qugate_mat_y, mat_y };
    test_t test_z = { qugate_mat_z, mat_z };
    test_t test_h = { qugate_mat_h, mat_h };
    test_t test_2x2s[N_TESTS_2X2] = {
        test_i,
        test_x,
        test_y,
        test_z,
        test_h
    };

    test_t test_cx = { qugate_mat_cx, mat_cx };
    test_t test_cz = { qugate_mat_cz, mat_cz };
    test_t test_ch = { _qugate_mat_ch, mat_ch };
    test_t test_4x4s[N_TESTS_4X4] = {
        test_cx,
        test_cz,
        test_ch
    };
    
    xiy mat_input[16];

    for (int i = 0; i < N_TESTS_2X2; i++) {
        test_t test = test_2x2s[i];
        qugate_mat_error(mat_input);
        test.func(mat_input);
        for (int j = 0; j < 4; j++) {
            if (!xiy_equals(mat_input[j], test.output[j])) {
                printf("TEST -- qugate -- FAILED -- 2x2 %i: Expected qugate to be\n", i);
                xiy_print_2x2(test.output);
                printf("but got\n");
                xiy_print_2x2(mat_input);
                exit(1);
            }
        }
    }

    for (int i = 0; i < N_TESTS_4X4; i++) {
        test_t test = test_4x4s[i];
        qugate_mat_error(mat_input);
        test.func(mat_input);
        for (int j = 0; j < 16; j++) {
            if (!xiy_equals(mat_input[j], test.output[j])) {
                printf("TEST -- qugate -- FAILED -- 4x4 %i: Expected qugate to be\n", i);
                xiy_print_4x4(test.output);
                printf("but got\n");
                xiy_print_4x4(mat_input);
                exit(1);
            }
        };
    }

    printf("TEST -- qugate -- SUCCESS\n");
}
