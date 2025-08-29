#define _USE_MATH_DEFINES
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../src/qucircuit/qucircuit_apply.h"
#include "../../src/qugate/qugate_mat.h"
#include "../../src/qubits/qubits_apply.h"

//
// 'main.c'
//

/*
    Command line application.
    Applies Grover's Algorithm to a state to amplify a particular state from a fully uniform state.
    Requires first argument, the integer representing the state to amplify.
    If a second argument is provided, enables logging at each iteration of the algorithm.
*/

//
// 'main.c' defines
//

#define N_QUBITS 14
#define N_VALUES (1 << N_QUBITS)

//
// 'main.c' type definitions
//

typedef struct {
    int index;
    double probability;
} index_probability;

//
// 'main.c' function definitions
//

void check_args(int argc, char *argv[], int *x, int *do_log);
void find_zeros(int x, int n_bits, int *n_zeros, int *zeros);
void qubits_init_0(qubits qs);
index_probability qubits_most_probable(qubits qs);

//
// 'main.c' entry point
//

int main(int argc, char *argv[]) {
    int x;
    int do_log;
    check_args(argc, argv, &x, &do_log);

    qubits qs;
    xiy qs_space[2 * N_VALUES];
    qubits_init(&qs, N_QUBITS, qs_space, qs_space+N_VALUES);

    int inputs[N_QUBITS];
    for (int i = 0; i < N_QUBITS; i++) {
        inputs[i] = i;
    }
    
    int qcc_space[5 * N_QUBITS]; // I haven't figured out how much space is needed tbh
    qucircuit_context qcc = qucircuit_context_init(N_QUBITS, qcc_space);

    //
    // Base Operators
    //

    // Create a qucircuit "HAll" that applies the 'H' gate to all qubits
    qucircuit qc_ha;
    qucircuit_init_func_mu(&qc_ha, "HAll", N_QUBITS, qugate_func_mh);
    qucircuit_application qca_ha = { .target_qubits=inputs, .circuit=&qc_ha };

    // Create a qucircuit "XAll" that applies the 'X' gate to all qubits
    qucircuit qc_xa;
    qucircuit_init_func_mu(&qc_xa, "XAll", N_QUBITS, qugate_func_mx);
    qucircuit_application qca_xa = { .target_qubits=inputs, .circuit=&qc_xa };

    // Create a qucircuit "MCZAll" that applies the 'Z' gate only when all qubits are 1
    qucircuit qc_mcza;
    if (N_QUBITS > 1) {
        qucircuit_init_func_mcu(&qc_mcza, "MCZAll", N_QUBITS-1, qugate_func_mcz);
    } else {
        qucircuit_init_func_u(&qc_mcza, "Z", qugate_func_z);
    }
    qucircuit_application qca_mcza = { .target_qubits=inputs, .circuit=&qc_mcza };

    //
    // Oracle Operator
    //

    // Create a qucircuit "XZeros" that flips all bits that are zeros of x
    qucircuit qc_x_zeros;
    int n_x_zeros;
    int x_zeros[N_QUBITS];
    find_zeros(x, N_QUBITS, &n_x_zeros, x_zeros);
    if (n_x_zeros) {
        qucircuit_init_func_mu(&qc_x_zeros, "XZeros", n_x_zeros, qugate_func_mx);
    } else {
        qucircuit_init_parent(&qc_x_zeros, "XZerosNone", 0, 0, NULL);
    }
    qucircuit_application qca_x_zeros = { .target_qubits=x_zeros, .circuit=&qc_x_zeros };

    // Create a qucircuit "Oracle" that negates only if the state = x
    // Does this by flipping all zeros of x, negating if the state is all ones, and flipping all zeros of x again
    qucircuit qc_oracle;
    qucircuit_application qc_oracle_children[3] = {
        qca_x_zeros,
        qca_mcza,
        qca_x_zeros
    };
    qucircuit_init_parent(&qc_oracle, "Oracle", N_QUBITS, 3, qc_oracle_children);
    qucircuit_application qca_oracle = { .target_qubits=inputs, .circuit=&qc_oracle };

    //
    // Grover Diffusion Operator
    //

    // Create a qucircuit "GroverDiffusion" that applies "HAll", "XAll", "MCZAll", "XAll", "HAll"
    qucircuit qc_grover_diffusion;
    qucircuit_application qc_grover_diffusion_children[5] = {
        qca_ha,
        qca_xa,
        qca_mcza,
        qca_xa,
        qca_ha
    };
    qucircuit_init_parent(&qc_grover_diffusion, "GroverDiffusion", N_QUBITS, 5, qc_grover_diffusion_children);
    qucircuit_application qca_grover_diffusion = { .target_qubits=inputs, .circuit=&qc_grover_diffusion };

    //
    // Grover's Algorithm Iteration Operator
    //

    // Create a qucircuit "GroverIteration" that applies "Oracle", "GroverDiffusion"
    qucircuit qc_grover_iteration;
    qucircuit_application qc_grover_iteration_children[2] = {
        qca_oracle,
        qca_grover_diffusion
    };
    qucircuit_init_parent(&qc_grover_iteration, "GroverIteration", N_QUBITS, 2, qc_grover_iteration_children);
    qucircuit_application qca_grover_iteration = { .target_qubits=inputs, .circuit=&qc_grover_iteration };

    //
    // Run Grover's Algorithm
    //

    // Initialize to uniform state
    qubits_init_0(qs);
    qucircuit_apply(&qs, qcc, &qca_ha);

    // Run "GroverDiffusion" n=pi/4*sqrt(N_VALUES) times
    int n_iterations = (int)ceil(M_PI_4 * sqrt(N_VALUES));
    printf("All numbers from 0 to %i:\nAmplifying value %i.\nTotal iterations: pi/4*sqrt(%i)=%i times.\n", N_VALUES-1, x, N_VALUES-1, n_iterations);
    for (int i = 0; i < n_iterations; i++) {
        if (do_log) {
            printf("Iteration #%i:\n", i+1);
        }
        qucircuit_apply(&qs, qcc, &qca_grover_iteration);
        if (do_log) {
            index_probability most_probable = qubits_most_probable(qs);
            printf("Most probable: %i, %.2lf%%\n", most_probable.index, most_probable.probability * 100);
        }
    }
    index_probability most_probable = qubits_most_probable(qs);
    printf("Most probable value: %i\nProbability: %.02lf%%\n", most_probable.index, most_probable.probability * 100);
}

//
// 'main.c' function implementations
//

void check_args(int argc, char *argv[], int *x, int *do_log) {
    if (argc < 2) {
        printf("Please enter a number to search for between 0 and %i.\n", N_VALUES-1);
        exit(1);
    }
    *x = atoi(argv[1]);
    if ((*x < 0) || (*x >= N_VALUES)) {
        printf("Please enter a number to search for between 0 and %i.\n", N_VALUES-1);
        exit(1);
    }
    *do_log = argc > 2;
}

void find_zeros(int x, int n_bits, int *n_zeros, int *zeros) {
    // x_flipped has a 1 everywhere x has a zero (within n_bits)
    int bit_mask = (1 << n_bits) - 1;
    int x_flipped = (~x) & bit_mask;
    *n_zeros = 0;
    int bit_index = 0;
    while (x_flipped) {
        if (x_flipped % 2) {
            zeros[*n_zeros] = bit_index;
            *n_zeros += 1;
        }
        bit_index++;
        x_flipped >>= 1;
    }
}

void qubits_init_0(qubits qs) {
    qs.values_in[0] = xiy_one;
    for (int i = 1; i < qs.n_values; i++) {
        qs.values_in[i] = xiy_zero;
    }
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
