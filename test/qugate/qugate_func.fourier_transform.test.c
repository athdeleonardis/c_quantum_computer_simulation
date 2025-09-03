#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/qugate/qugate_func.h"

#define EPSILON 1e-9
#define N_QUBITS 4
#define N_VALUES (1 << N_QUBITS)

void xiy_copy(int n_values, xiy *in, xiy *out);
int xiy_equal(xiy z1, xiy z2);
int xiyn_equal(int n_values, xiy *zs1, xiy *zs2);
void xiyn_print(int n_values, xiy *zs);

int main(int argc, char *argv[]) {
    qubits qs;
    xiy qs_space[3 * N_VALUES];
    int inputs[N_QUBITS];
    for (int i = 0; i < N_VALUES; i++) {
        qs_space[i] = xiy_mul_s(xiy_one, i+1);
    }
    for (int i = 0; i < N_QUBITS; i++) {
        inputs[i] = i;
    }

    // Check inverse of eachother
    xiy_copy(N_VALUES, qs_space, qs_space+N_VALUES);
    qubits_init(&qs, N_QUBITS, qs_space+N_VALUES, qs_space+2*N_VALUES);
    qugate_func_fourier_transform(&qs, N_QUBITS, inputs);
    qugate_func_fourier_transform_inverse(&qs, N_QUBITS, inputs);
    if (!xiyn_equal(N_VALUES, qs_space, qs.values_in)) {
        printf("TEST -- qugate_func.fourier_transform -- FAILED -- Inverse\n");
        printf("Expected state:\n");
        xiyn_print(N_VALUES, qs_space);
        printf("Resulting state:\n");
        xiyn_print(N_VALUES, qs.values_in);
        exit(1);
    }

    printf("TEST -- qugate_func.fourier_transform -- SUCCESS\n");
}

void xiy_copy(int n_values, xiy *in, xiy *out) {
    for (int i = 0; i < n_values; i++) {
        out[i] = in[i];
    }
}

int xiy_equal(xiy z1, xiy z2) {
    return fabs(z1.x - z2.x) < EPSILON && fabs(z1.y - z2.y) < EPSILON;
}

int xiyn_equal(int n_values, xiy *zs1, xiy *zs2) {
    for (int i = 0; i < n_values; i++) {
        if (!xiy_equal(zs1[i], zs2[i])) {
            return 0;
        }
    }
    return 1;
}

void xiyn_print(int n_values, xiy *zs) {
    printf("[");
    int do_print_comma = 0;
    for (int i = 0; i < n_values; i++) {
        if (do_print_comma) {
            printf(", ");
        }
        do_print_comma = 1;
        printf("{%.02lf, %.02lf}", zs[i].x, zs[i].y);
    }
    printf("]\n");
}
