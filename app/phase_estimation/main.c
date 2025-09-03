#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "../../src/qubits/qubits.h"
#include "../../src/qugate/qugate_func.h"

#define N_ESTIMATE_QUBITS 5
#define N_EIGENVECTOR_QUBITS 1
#define N_QUBITS (N_EIGENVECTOR_QUBITS + N_ESTIMATE_QUBITS)
#define N_VALUES (1 << N_QUBITS)

typedef struct value_probability {
    int value;
    double probability;
} value_probability;

void check_args(int argc, char *argv[], double *angle);
void qubits_init_1(qubits qs);
void qugate_func_cpn(qubits *qs, int qc, int qt, double angle, int n);
void qugate_func_phase_application(qubits *qs, int n_estimate_qubits, int *estimate_qubits, int eigenvector_qubit, double angle);
value_probability find_most_probable(qubits qs);
double state_index_to_angle_multiplier(int index);

int main(int argc, char *argv[]) {
    double angle;
    check_args(argc, argv, &angle);
    printf("Checking with phase %lf\n", angle);

    int inputs[N_QUBITS];
    for (int i = 0; i < N_QUBITS; i++) {
        inputs[i] = i;
    }

    xiy qs_space[2 * N_VALUES];
    qubits qs;
    qubits_init(&qs, N_QUBITS, qs_space, qs_space+N_VALUES);

    // Apply the algorithm:
    
    qubits_init_1(qs);
    qugate_func_mh(&qs, N_ESTIMATE_QUBITS, inputs+1);
    qugate_func_phase_application(&qs, N_ESTIMATE_QUBITS, inputs+1, 0, angle);
    qugate_func_fourier_transform_inverse(&qs, N_ESTIMATE_QUBITS, inputs+1);

    value_probability most_probable = find_most_probable(qs);
    most_probable.value >>= 1; // Remove eigenvector qubit
    double angle_multiplier_measured = state_index_to_angle_multiplier(most_probable.value);
    
    printf("Most probable: %i\nProbability: %lf%%\n", most_probable.value, most_probable.probability * 100);
    printf("Most probable bits: ");
    for (int i = 0; i < N_ESTIMATE_QUBITS; i++) {
        printf("%i", (most_probable.value >> i) & 1);
    }
    printf("\n");
    printf("Angle measured: 2pi * %lf\n = %lf\n", angle_multiplier_measured, 2 * M_PI * angle_multiplier_measured);
}

void check_args(int argc, char *argv[], double *angle) {
    if (argc < 2) {
        printf("Enter an angle in radians.\n");
        exit(1);
    }
    *angle = strtod(argv[1], NULL);
}

void qubits_init_1(qubits qs) {
    qs.values_in[0] = xiy_zero;
    qs.values_in[1] = xiy_one;
    for (int i = 2; i < qs.n_values; i++) {
        qs.values_in[i] = xiy_zero;
    }
}

void qugate_func_cpn(qubits *qs, int qc, int qt, double angle, int n) {
    int selector = (1 << qc) | (1 << qt);

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if ((s & selector) == selector) {
            qs->values_in[s] = xiy_mul(xiy_from_angle(angle * n), qs->values_in[s]);
        }
    }
}

// void qugate_func_phase_application(qubits *qs, int n_estimate_qubits, int *estimate_qubits, int eigenvector_qubit, double angle) {
//     for (int i = n_estimate_qubits-1; i > -1; i--) {
//         printf("Multiplying by angle %i times\n", 1 << (n_estimate_qubits - i - 1));
//         qugate_func_cpn(qs, estimate_qubits[i], eigenvector_qubit, angle, 1 << (n_estimate_qubits - i - 1));
//     }
// }

void qugate_func_phase_application(qubits *qs, int n_estimate_qubits, int *estimate_qubits, int eigenvector_qubit, double angle) {
    for (int i = 0; i < n_estimate_qubits; i++) {
        qugate_func_cpn(qs, estimate_qubits[i], eigenvector_qubit, angle, 1 << i);
    }
}

value_probability find_most_probable(qubits qs) {
    int value = -1;
    double probability = 0;
    for (int i = 0; i < qs.n_values; i++) {
        double probability_n = xiy_len(qs.values_in[i]);
        if (probability_n > probability) {
            value = i;
            probability = probability_n;
        }
    }
    value_probability vp = { .value=value, .probability=probability };
    return vp;
}

double state_index_to_angle_multiplier(int index) {
    double value = 0;
    int power = 1;
    while (index) {
        value += ((double)(index % 2)) / (1 << power);
        power++;
        index >>= 1;
    }
    return value;
}
