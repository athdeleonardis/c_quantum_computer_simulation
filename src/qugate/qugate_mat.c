#define _USE_MATH_DEFINES
#include <math.h>
#include "./qugate_mat.h"

void qugate_mat_i(xiy *mat_2x2) {
    mat_2x2[0] = xiy_one;
    mat_2x2[1] = xiy_zero;
    mat_2x2[2] = xiy_zero;
    mat_2x2[3] = xiy_one;
}

void qugate_mat_x(xiy *mat_2x2) {
    mat_2x2[0] = xiy_zero;
    mat_2x2[1] = xiy_one;
    mat_2x2[2] = xiy_one;
    mat_2x2[3] = xiy_zero;
}

void qugate_mat_y(xiy *mat_2x2) {
    mat_2x2[0] = xiy_zero;
    mat_2x2[1] = xiy_mul_s(xiy_i, -1);
    mat_2x2[2] = xiy_i;
    mat_2x2[3] = xiy_zero;
}

void qugate_mat_z(xiy *mat_2x2) {
    mat_2x2[0] = xiy_one;
    mat_2x2[1] = xiy_zero;
    mat_2x2[2] = xiy_zero;
    mat_2x2[3] = xiy_mul_s(xiy_one, -1);
}

void qugate_mat_h(xiy *mat_2x2) {
    double c = 1/sqrt(2);
    mat_2x2[0] = xiy_mul_s(xiy_one, c);
    mat_2x2[1] = mat_2x2[0];
    mat_2x2[2] = mat_2x2[0];
    mat_2x2[3] = xiy_mul_s(mat_2x2[0], -1);
}

void qugate_mat_p(xiy *mat_2x2, double angle) {
    mat_2x2[0] = xiy_one;
    mat_2x2[1] = xiy_zero;
    mat_2x2[2] = xiy_zero;
    mat_2x2[3] = xiy_from_angle(angle);
}

void qugate_mat_s(xiy *mat_2x2) {
    qugate_mat_p(mat_2x2, M_PI / 2);
}

void qugate_mat_t(xiy *mat_2x2) {
    qugate_mat_p(mat_2x2, M_PI / 4);
}

void qugate_mat_sd(xiy *mat_2x2) {
    qugate_mat_p(mat_2x2, -M_PI / 2);
}

void qugate_mat_td(xiy *mat_2x2) {
    qugate_mat_p(mat_2x2, -M_PI / 4);
}

void qugate_mat_cx(xiy *mat_4x4) {
    for (int i = 1; i < 16; i++) {
        mat_4x4[i] = xiy_zero;
    }
    mat_4x4[0] = xiy_one;
    mat_4x4[5] = xiy_one;
    mat_4x4[11] = xiy_one;
    mat_4x4[14] = xiy_one;
}

void qugate_mat_cz(xiy *mat_4x4) {
    for (int i = 1; i < 15; i++) {
        mat_4x4[i] = xiy_zero;
    }
    mat_4x4[0] = xiy_one;
    mat_4x4[5] = xiy_one;
    mat_4x4[10] = xiy_one;
    mat_4x4[15] = xiy_mul_s(xiy_one, -1);
}

void qugate_mat_cu(xiy *mat_4x4, xiy *mat_2x2) {
    for (int i = 1; i < 14; i++) {
        mat_4x4[i] = xiy_zero;
    }
    mat_4x4[0] = xiy_one;
    mat_4x4[5] = xiy_one;
    mat_4x4[10] = mat_2x2[0];
    mat_4x4[11] = mat_2x2[1];
    mat_4x4[14] = mat_2x2[2];
    mat_4x4[15] = mat_2x2[3];
}

void qugate_mat_swap(xiy *mat_4x4) {
    for (int i = 1; i < 15; i++) {
        mat_4x4[i] = xiy_zero;
    }
    mat_4x4[0] = xiy_one;
    mat_4x4[6] = xiy_one;
    mat_4x4[9] = xiy_one;
    mat_4x4[15] = xiy_one;
}
