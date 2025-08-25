#include <stdio.h>
#include <stdlib.h>
#include "../../src/qucircuit/qucircuit_context.h"

#define N_QUBITS 9
#define N_TESTS 5

typedef struct test {
    int n_inputs;
    int *inputs;
    int *outputs;
} test;

void qucircuit_context_print(qucircuit_context qcc) {
    printf("quricuit_context{ n_qubits: %i, input_to_qubit_stack: [", qcc.n_qubits);
    int do_print_comma = 0;
    for (int i = 0; i < qcc.n_qubits; i++) {
        if (do_print_comma)
            printf(", ");
        do_print_comma = 1;
        printf("%i", qcc.input_to_qubit_stack[i]);
    }
    printf("] }\n");
}

void print_error_details(qucircuit_context qcc_input, int n_inputs, int *inputs, qucircuit_context qcc_expected, qucircuit_context qcc_result) {
    printf("Input:    ");
    if (inputs == NULL)
        printf("None\n");
    else
        qucircuit_context_print(qcc_input);
    printf("Inputs:   ");
    if (inputs == NULL)
        printf("None");
    else {
        for (int i = 0; i < n_inputs; i++)
            printf("%i, ", inputs[i]);
    }
    printf("\nExpected: ");
    qucircuit_context_print(qcc_expected);
    printf("Result:   ");
    qucircuit_context_print(qcc_result);
}

int main(int argc, char *argv) {
    int stack[N_QUBITS * N_TESTS];
    qucircuit_context qcc_input = qucircuit_context_init(N_QUBITS, stack);

    int *t0_inputs = NULL;
    int t0_outputs[N_QUBITS] = { 0, 1, 2, 3, 4, 5, 6, 7, 8 };
    int t1_inputs[4] = { 1, 3, 5, 8 };
    int *t1_outputs = t1_inputs;
    int t2_inputs[4] = { 0, 2, 1, 3 };
    int t2_outputs[4] = { 1, 5, 3, 8 };
    int t3_inputs[3] = { 3, 0, 1 };
    int t3_outputs[3] = { 8, 1, 5 };
    int t4_inputs[1] = { 2 };
    int t4_outputs[1] = { 5 };

    test t0 = { N_QUBITS, t0_inputs, t0_outputs };
    test t1 = { 4, t1_inputs, t1_outputs };
    test t2 = { 4, t2_inputs, t2_outputs };
    test t3 = { 3, t3_inputs, t3_outputs };
    test t4 = { 1, t4_inputs, t4_outputs };
    test tests[N_TESTS] = {
        t0,
        t1,
        t2,
        t3,
        t4
    };

    for (int i = 0; i < N_TESTS; i++) {
        test t = tests[i];
        qucircuit_context qcc_result;
        if (t.inputs != NULL)
            qcc_result = qucircuit_context_push(&qcc_input, t.n_inputs, t.inputs);
        else
            qcc_result = qcc_input;
        qucircuit_context qcc_expected = { .n_qubits=t.n_inputs, .input_to_qubit_stack=t.outputs };
        if (qcc_result.n_qubits != t.n_inputs) {
            printf("TEST -- qucircuit_context -- FAILED -- test %i n_qubits\n", i);
            print_error_details(qcc_input, t.n_inputs, t.inputs, qcc_expected, qcc_result);
            exit(1);
        }
        for (int i = 0; i < t.n_inputs; i++) {
            if (qcc_result.input_to_qubit_stack[i] != qcc_expected.input_to_qubit_stack[i]) {
                printf("TEST -- qucircuit_context -- FAILED -- test %i input_to_qubit_stack\n", i);
                print_error_details(qcc_input, t.n_inputs, t.inputs, qcc_expected, qcc_result);
                exit(1);
            }
        }

        qcc_input = qcc_result;
    }

    printf("TEST -- qucircuit_context -- SUCCESS\n");
}