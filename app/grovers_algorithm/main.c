#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../src/qucircuit/qucircuit_apply.h"
#include "../../src/qugate/qugate.h"
#include "../../src/qubits/qubits_apply.h"

#define N_QUBITS 8
#define N_VALUES (1 << N_QUBITS)

void qubits_init_0(qubits qs);
void qubits_oracle(qubits qs, int x);
void qubits_mcza(qubits qs);

typedef struct {
    int index;
    double probability;
} index_probability;

index_probability qubits_most_probable(qubits qs);
// void qubits_print(qubits qs);

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Please enter a number to search for between 0 and %i.\n", N_VALUES);
        exit(1);
    }
    int x = atoi(argv[1]);
    if (x >= N_VALUES) {
        printf("Please enter a number to search for between 0 and %i.\n", N_VALUES);
        exit(1);
    }

    qubits qs;
    xiy qs_space[4*N_VALUES];
    qubits_init(&qs, N_QUBITS, qs_space, qs_space+N_VALUES);

    int qcc_space[N_QUBITS * 4];

    int inputs[N_QUBITS];
    for (int i = 0; i < N_QUBITS; i++) {
        inputs[i] = i;
    }

    xiy mat_h[4];
    qugate_h(mat_h);
    qucircuit qc_h;
    qucircuit_init_2x2(&qc_h, "H", mat_h);

    xiy mat_x[4];
    qugate_x(mat_x);
    qucircuit qc_x;
    qucircuit_init_2x2(&qc_x, "X", mat_x);

    // Create a qucircuit "Uniform" that applies the Hadamard gate to every qubit
    qucircuit qc_uniform;
    qucircuit_application qc_uniform_children[N_QUBITS];
    qucircuit_application qca_uniform = { .target_qubits=inputs, .circuit=&qc_uniform };
    for (int i = 0; i < N_QUBITS; i++) {
        qc_uniform_children[i].target_qubits = inputs + i;
        qc_uniform_children[i].circuit = &qc_h;
    }
    qucircuit_init_parent(&qc_uniform, "Uniform", N_QUBITS, N_QUBITS, qc_uniform_children);

    // Create a qucircuit "XAll" that flips every qubit
    qucircuit qc_xa;
    qucircuit_application qc_xa_children[N_QUBITS];
    qucircuit_application qca_xa = { .target_qubits=inputs, .circuit=&qc_xa };
    for (int i = 0; i < N_QUBITS; i++) {
        qc_xa_children[i].target_qubits = inputs + i;
        qc_xa_children[i].circuit = &qc_x;
    }
    qucircuit_init_parent(&qc_xa, "XAll", N_QUBITS, N_QUBITS, qc_xa_children);

    // Create a qucircuit "Oracle" that negates only if the state = x

    // Create a qucircuit "GroverDiffusion" that applies "Uniform", "XAll", "MCZAll", "XAll", "Uniform"

    // Create a circuit "GroverIteration" that applies "Oracle", "GroverDiffusion"

    //
    // Run the algorithm
    //

    qucircuit_context qcc = qucircuit_context_init(N_QUBITS, qcc_space);

    qubits_init_0(qs);
    qucircuit_apply(&qs, qcc, &qca_uniform);

    // Run "GroverDiffusion" n=pi/4*sqrt(N_VALUES) times
    int n = (int)ceil(M_PI_4 * sqrt(N_VALUES));
    for (int i = 0; i < n; i++) {
        printf("Iteration #%i:\n", i);

        qubits_oracle(qs, x);

        // GroverDiffusion
        qucircuit_apply(&qs, qcc, &qca_uniform);
        qucircuit_apply(&qs, qcc, &qca_xa);
        qubits_mcza(qs);
        qucircuit_apply(&qs, qcc, &qca_xa);
        qucircuit_apply(&qs, qcc, &qca_uniform);

        index_probability most_probable = qubits_most_probable(qs);
        printf("Most probable: %i, %.2lf%%\n", most_probable.index, most_probable.probability * 100);
    }
}

void qubits_init_0(qubits qs) {
    qs.values_in[0] = xiy_one;
    for (int i = 1; i < qs.n_values; i++) {
        qs.values_in[i] = xiy_zero;
    }
}

void qubits_oracle(qubits qs, int x) {
    qs.values_in[x] = xiy_mul_s(qs.values_in[x], -1);
}

void qubits_mcza(qubits qs) {
    qubits_oracle(qs, N_VALUES-1);
}

index_probability qubits_most_probable(qubits qs) {
    int value = -1;
    double probability = 0;
    for (int i = 0; i < N_VALUES; i++) {
        double probability_n = xiy_len(qs.values_in[i]);
        if (probability_n > probability) {
            value = i;
            probability = probability_n;
        }
    }
    index_probability ret = { value, probability };
    return ret;
}

// void qubits_print(qubits qs) {
//     printf("qubits{ n_qubits=%i, n_values=%i, values_in=[", qs.n_qubits, qs.n_values);
//     for (int i = 0; i < qs.n_values; i++) {
//         printf("{%.2lf,%.2lf}, ", qs.values_in[i].x, qs.values_in[i].y);
//     }
//     printf("] }\n");
// }
