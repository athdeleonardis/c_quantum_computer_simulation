#include <math.h>
#include "../../src/qucircuit/qucircuit_apply.h"
#include "../../src/qugate/qugate_mat.h"
#include "../../src/qubits/qubits_apply.h"

#define EPSILON 1e-9
#define N_QUBITS 2
#define N_VALUES (1 << N_QUBITS)

void qubits_state_init(qubits qs) {
    for (int i = 0; i < N_QUBITS; i++) {
        qs.values_in[i] = xiy_mul_s(xiy_one, i+1);
    }
}

int qubits_equal(qubits qs0, qubits qs1) {
    for (int i = 0; i < N_VALUES; i++) {
        if (!xiy_equal(qs0.values_in[i], qs1.values_in[i])) {
            return 0;
        }
    }
    return 1;
}

int xiy_equal(xiy z0, xiy z1) {
    return fabs(z0.x - z1.x) < EPSILON && fabs(z0.y - z1.y) < EPSILON;
}

void qubits_print(qubits qs) {
    printf("qubits{ n_qubits=%i, n_values=%i, values_in=[", qs.n_qubits, qs.n_values);
    int do_print_comma = 0;
    for (int i = 0; i < qs.n_values; i++) {
        if (do_print_comma)
            printf(", ");
        do_print_comma = 1;
        printf("{%.2lf,%.2lf}", qs.values_in[i].x, qs.values_in[i].y);
    }
    printf("] }\n");
}

void print_error_context(qubits qs_expected, qubits qs_result) {
    printf("Expected:\n");
    qubits_print(qs_expected);
    printf("Result:\n");
    qubits_print(qs_result);
}

int main(int argc, char *argv) {
    int inputs[3] = { 0, 1, 0 };

    xiy qs_space[4 * N_VALUES];
    qubits qs_result;
    qubits_init(&qs_result, N_QUBITS, qs_space, qs_space+N_VALUES);
    qubits qs_expected;
    qubits_init(&qs_expected, N_QUBITS, qs_space+2*N_VALUES, qs_space+3*N_VALUES);
    int qcc_space[4 * N_QUBITS];
    qucircuit_context qcc = qucircuit_context_init(N_QUBITS, qcc_space);

    xiy mat_x[4];
    qugate_mat_x(mat_x);
    qucircuit qc_x;
    qucircuit_init_2x2(&qc_x, "X", mat_x);
    qucircuit_application qca_x = { .circuit=&qc_x, .target_qubits=inputs };

    xiy mat_z[4];
    qugate_mat_z(mat_z);
    qucircuit qc_z;
    qucircuit_init_2x2(&qc_z, "Z", mat_z);
    qucircuit_application qca_z = { .circuit=&qc_z, .target_qubits=inputs };

    xiy mat_cx[16];
    qugate_mat_cx(mat_cx);
    qucircuit qc_cx;
    qucircuit_init_4x4(&qc_cx, "CX", mat_cx);

    qucircuit qc_x_z;
    qucircuit_application qc_x_z_children[2] = { qca_x, qca_z };
    qucircuit_init_parent(&qc_x_z, "XZ", 1, 2, qc_x_z_children);
    qucircuit_application qca_x_z = { .circuit=&qc_x_z, .target_qubits=inputs };
    
    qucircuit qc_z_x;
    qucircuit_application qc_z_x_children[2] = { qca_z, qca_x };
    qucircuit_init_parent(&qc_z_x, "ZX", 1, 2, qc_z_x_children);
    qucircuit_application qca_z_x = { .circuit=&qc_z_x, .target_qubits=inputs };

    qucircuit qc_x_z_z_x;
    qucircuit_application qc_z_x_x_z_children[2] = { qca_x_z, qca_z_x };
    qucircuit_init_parent(&qc_x_z_z_x, "XZZX", 1, 2, qc_z_x_x_z_children);
    qucircuit_application qca_x_z_z_x = { .circuit=&qc_x_z_z_x, .target_qubits=inputs };

    qucircuit qc_swap;
    qucircuit_application qc_swap_children[3];
    qc_swap_children[0].circuit = &qc_cx;
    qc_swap_children[0].target_qubits = inputs;
    qc_swap_children[1].circuit = &qc_cx;
    qc_swap_children[1].target_qubits = inputs + 1;
    qc_swap_children[2].circuit = &qc_cx;
    qc_swap_children[2].target_qubits = inputs;
    qucircuit_init_parent(&qc_swap, "SWAP", 2, 3, qc_swap_children);
    qucircuit_application qca_swap = { .circuit=&qc_swap, .target_qubits=inputs };

    // Test XZ
    {
        qubits_state_init(qs_result);
        qubits_state_init(qs_expected);

        qucircuit_apply(&qs_result, qcc, &qca_x_z);
        qubits_apply_2x2(&qs_expected, mat_x, 0);
        qubits_apply_2x2(&qs_expected, mat_z, 0);

        if (!qubits_equal(qs_result, qs_expected)) {
            printf("TEST -- qucircuit_apply -- FAILED -- XZ\n");
            print_error_context(qs_expected, qs_result);
            exit(1);
        }
    }

    // Test XZZX
    {
        qubits_state_init(qs_result);
        qubits_state_init(qs_expected);

        qucircuit_apply(&qs_result, qcc, &qca_x_z_z_x);

        if (!qubits_equal(qs_result, qs_expected)) {
            printf("TEST -- qucircuit_apply -- FAILED -- XZZX\n");
            print_error_context(qs_expected, qs_result);
            exit(1);
        }
    }

    // Test SWAP
    {
        qubits_state_init(qs_result);
        qubits_state_init(qs_expected);

        qucircuit_apply(&qs_result, qcc, &qca_swap);

        qubits_apply_4x4(&qs_expected, mat_cx, 0, 1);
        qubits_apply_4x4(&qs_expected, mat_cx, 1, 0);
        qubits_apply_4x4(&qs_expected, mat_cx, 0, 1);

        if (!qubits_equal(qs_result, qs_expected)) {
            printf("TEST -- qucircuit_apply -- FAILED -- SWAP\n");
            print_error_context(qs_expected, qs_result);
            exit(1);
        }
    }

    printf("TEST -- qucircuit_apply -- SUCCESS\n");
}
