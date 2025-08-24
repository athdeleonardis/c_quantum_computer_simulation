#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/qubits/qubits_apply.h"
#include "../../src/qugate/qugate.h"

#define EPSILON 1e-9
#define N_QUBITS 3
#define N_VALUES 8
#define N_2X2_TESTS 8
#define N_4X4_TESTS 4

typedef struct test_2x2 {
    xiy *mat;
    int q;
    xiy *output;
} test_2x2;

typedef struct test_4x4 {
    xiy *mat;
    int q1;
    int q2;
    xiy *output;
} test_4x4;

void copy_state(qubits *qs, xiy *state) {
    for (int i = 0; i < N_VALUES; i++) {
        qs->values_in[i] = state[i];
    }
}

int check_xiy(xiy a, xiy b) {
    return labs(a.x - b.x) < EPSILON && labs(a.y - b.y) < EPSILON;
}

int check_state(qubits *qs, xiy *state) {
    for (int i = 0; i < N_VALUES; i++) {
        if (!check_xiy(qs->values_in[i], state[i]))
            return 0;
    }
    return 1;
}

void print_state(qubits *qs, xiy *state) {
    printf("Expected vs Result:\n");
    for (int i = 0; i < N_VALUES; i++) {
        printf("%i%i%i -- { %lf, %lf } -- { %lf, %lf }\n", (i / 4) % 2, (i / 2) % 2, i % 2, state[i].x, state[i].y, qs->values_in[i].x, qs->values_in[i].y);
    }
}


void xiy_print_2x2(xiy *mat) {
    printf("Matrix:\n");
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

int main(int argc, char *argv[]) {
    xiy mat_empty_2x2[4] = { xiy_zero, xiy_zero, xiy_zero, xiy_zero };

    xiy mat_i[4];
    qugate_i(mat_i);
    xiy mat_x[4];
    qugate_x(mat_x);
    xiy mat_y[4];
    qugate_y(mat_y);
    xiy mat_z[4];
    qugate_z(mat_z);
    xiy mat_h[4];
    qugate_h(mat_h);

    xiy mat_cx[16];
    qugate_cx(mat_cx);
    xiy mat_cz[16];
    qugate_cz(mat_cz);
    
    qubits qs;
    xiy space[2*N_VALUES];
    qubits_init(&qs, 3, space, space+N_VALUES);

    xiy c1 = xiy_one;
    xiy c2 = xiy_mul_s(xiy_one, 2);
    xiy c3 = xiy_mul_s(xiy_one, 3);
    xiy c4 = xiy_mul_s(xiy_one, 4);
    xiy c5 = xiy_mul_s(xiy_one, 5);
    xiy c6 = xiy_mul_s(xiy_one, 6);
    xiy c7 = xiy_mul_s(xiy_one, 7);
    xiy c8 = xiy_mul_s(xiy_one, 8);
    
    xiy c1m = xiy_mul_s(xiy_one, -1);
    xiy c2m = xiy_mul_s(xiy_one, -2);
    xiy c3m = xiy_mul_s(xiy_one, -3);
    xiy c4m = xiy_mul_s(xiy_one, -4);
    xiy c5m = xiy_mul_s(xiy_one, -5);
    xiy c6m = xiy_mul_s(xiy_one, -6);
    xiy c7m = xiy_mul_s(xiy_one, -7);
    xiy c8m = xiy_mul_s(xiy_one, -8);

    xiy c1i = xiy_i;
    xiy c2i = xiy_mul_s(xiy_i, 2);
    xiy c3i = xiy_mul_s(xiy_i, 3);
    xiy c4i = xiy_mul_s(xiy_i, 4);
    xiy c5i = xiy_mul_s(xiy_i, 5);
    xiy c6i = xiy_mul_s(xiy_i, 6);
    xiy c7i = xiy_mul_s(xiy_i, 7);
    xiy c8i = xiy_mul_s(xiy_i, 8);

    xiy c1mi = xiy_mul_s(xiy_i, -1);
    xiy c2mi = xiy_mul_s(xiy_i, -2);
    xiy c3mi = xiy_mul_s(xiy_i, -3);
    xiy c4mi = xiy_mul_s(xiy_i, -4);
    xiy c5mi = xiy_mul_s(xiy_i, -5);
    xiy c6mi = xiy_mul_s(xiy_i, -6);
    xiy c7mi = xiy_mul_s(xiy_i, -7);
    xiy c8mi = xiy_mul_s(xiy_i, -8);

    // regular order
    //  000   001   010   011   100   101   110   111
    //   1     2     3     4     5     6     7     8
    xiy state_i[N_VALUES] = { c1, c2, c3, c4, c5, c6, c7, c8 };

    // mat_x flips a qubit
    // q=0
    //  000   001   010   011   100   101   110   111
    //  001   000   011   010   101   100   111   110
    //   2     1     4     3     6     5     8     7
    xiy state_x_0[N_VALUES] = { c2, c1, c4, c3, c6, c5, c8, c7 };
    // q=1
    //  000   001   010   011   100   101   110   111
    //  010   011   000   001   110   111   100   101
    //   3     4     1     2     7     8     5     6
    xiy state_x_1[N_VALUES] = { c3, c4, c1, c2, c7, c8, c5, c6 };
    // q=2
    //  000   001   010   011   100   101   110   111
    //  100   101   110   111   000   001   010   011
    //   5     6     7     8     1     2     3     4
    xiy state_x_2[N_VALUES] = { c5, c6, c7, c8, c1, c2, c3, c4 };
    // mat_y flips a qubit, and multiplies by i if it was previously 1, and -i if it was previously 0
    // q=1
    //  000   001   010   011   100   101   110   111
    //  010i  011i -000i -001i  110i  111i -100i -101i
    //  -3i   -4i    1i    2i   -7i   -8i    5i    6i
    xiy state_y_1[N_VALUES] = { c3mi, c4mi, c1i, c2i, c7mi, c8mi, c5i, c6i };
    // mat_z multiplies by -1 if the qubit is 1
    // q=1
    //  000   001   010   011   100   101   110   111
    //  000   001  -010  -011   100   101  -110  -111
    //   1     2    -3    -4     5     6    -7    -8
    xiy state_z_1[N_VALUES] = { c1, c2, c3m, c4m, c5, c6, c7m, c8m };
    // mat_cx flips q1 if q0 is 1
    // q0=0 q1=1
    //  000   001   010   011   100   101   110   111
    //  000   011   010   001   100   111   110   101
    //   1     4     3     2     5     8     7     6
    xiy state_cx_0_1[N_VALUES] = { c1, c4, c3, c2, c5, c8, c7, c6 };
    // q0=1 q1=2
    //  000   001   010   011   100   101   110   111
    //  000   001   110   111   100   101   010   011
    //   1     2     7     8     5     6     3     4
    xiy state_cx_1_2[N_VALUES] = { c1, c2, c7, c8, c5, c6, c3, c4 };
    // q0=2 q1=1
    //  000   001   010   011   100   101   110   111
    //  000   001   010   011   110   111   100   101
    //   1     2     3     4     7     8     5     6
    xiy state_cx_2_1[N_VALUES] = { c1, c2, c3, c4, c7, c8, c5, c6 };
    // mat_cz if q0 and q1 are 1, multiplies by -1
    //  000   001   010   011   100   101   110   111
    //  000   001   010   011   100   101  -110  -111
    //   1     2     3     4     5     6    -7    -8
    xiy state_cz_2_1[N_VALUES] = { c1, c2, c3, c4, c5, c6, c7m, c8m };

    test_2x2 test_i_0 = { mat_i, 0, state_i };
    test_2x2 test_i_1 = { mat_i, 1, state_i };
    test_2x2 test_i_2 = { mat_i, 2, state_i };
    test_2x2 test_x_0 = { mat_x, 0, state_x_0 };
    test_2x2 test_x_1 = { mat_x, 1, state_x_1 };
    test_2x2 test_x_2 = { mat_x, 2, state_x_2 };
    test_2x2 test_y_1 = { mat_y, 1, state_y_1 };
    test_2x2 test_z_1 = { mat_z, 1, state_z_1 };

    test_4x4 test_cx_0_1 = { mat_cx, 0, 1, state_cx_0_1 };
    test_4x4 test_cx_1_2 = { mat_cx, 1, 2, state_cx_1_2 };
    test_4x4 test_cx_2_1 = { mat_cx, 2, 1, state_cx_2_1 };
    test_4x4 test_cz_2_1 = { mat_cz, 2, 1, state_cz_2_1 };

    test_2x2 test_2x2s[N_2X2_TESTS] = {
        test_i_0, test_i_1, test_i_2,
        test_x_0, test_x_1, test_x_2,
        test_y_1,
        test_z_1
    };

    test_4x4 test_4x4s[N_4X4_TESTS] = {
        test_cx_0_1, test_cx_1_2, test_cx_2_1,
        test_cz_2_1
    };

    // Test apply 2x2
    for (int i = 0; i < N_2X2_TESTS; i++) {
        test_2x2 test = test_2x2s[i];
        copy_state(&qs, state_i);
        qubits_apply_2x2(&qs, test.mat, test.q);
        if (!check_state(&qs, test.output)) {
            printf("TEST -- qubits_apply -- FAILED -- 2x2 %i: Expected result to match state\n", i);
            xiy_print_2x2(test.mat);
            print_state(&qs, test.output);
            exit(0);
        }
    }

    // Test apply 4x4
    for (int i = 0; i < N_4X4_TESTS; i++) {
        test_4x4 test = test_4x4s[i];
        copy_state(&qs, state_i);
        qubits_apply_4x4(&qs, test.mat, test.q1, test.q2);
        if (!check_state(&qs, test.output)) {
            printf("TEST -- qubits_apply -- FAILED -- 4x4 %i: Expected result to match state\n", i);
            xiy_print_4x4(test.mat);
            print_state(&qs, test.output);
            exit(0);
        }
    }

    printf("TEST -- qubits_apply -- SUCCESS\n");
}
