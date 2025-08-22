#include <stdio.h>
#include <stdlib.h>

#include "../../src/qubits/qubits.h"

#define TEST_N_QUBITS 3
#define TEST_N_VALUES 1<<TEST_N_QUBITS
#define TEST_POINTER_A (xiy *)1
#define TEST_POINTER_B (xiy *)2

int main(int argc, char *argv[]) {
    // Test initialize
    qubits qs;
    qubits_init(&qs, TEST_N_QUBITS, TEST_POINTER_A, TEST_POINTER_B);
    if (qs.n_qubits != TEST_N_QUBITS) {
        printf("TEST -- qubits -- FAILED -- n_qubits: Expected qs.n_qubits=%i but got %i.\n", TEST_N_QUBITS, qs.n_qubits);
        exit(0);
    }
    if (qs.n_values != TEST_N_VALUES) {
        printf("TEST -- qubits -- FAILED -- n_values: Expected qs.n_values=%i but got %i.\n", TEST_N_VALUES, qs.n_values);
        exit(0);
    }
    if (qs.values_in != TEST_POINTER_A) {
        printf("TEST -- qubits -- FAILED -- values_in: Expected qs.values_in=%i but got %i.\n", TEST_POINTER_A, qs.values_in);
        exit(0);
    }
    if (qs.values_out != TEST_POINTER_B) {
        printf("TEST -- qubits -- FAILED -- values_out: Expected qs.values_out=%i but got %i.\n", TEST_POINTER_B, qs.values_out);
        exit(0);
    }
    
    // Test swap
    qubits_swap_in_out(&qs);
    if (qs.values_in != TEST_POINTER_B) {
        printf("TEST -- qubits -- FAILED -- values_in first swap: Expected qs.values_in=%i but got %i.\n", TEST_POINTER_B, qs.values_in);
        exit(0);
    }
    if (qs.values_out != TEST_POINTER_A) {
        printf("TEST -- qubits -- FAILED -- values_out first swap: Expected qs.values_out=%i but got %i.\n", TEST_POINTER_A, qs.values_out);
        exit(0);
    }
    qubits_swap_in_out(&qs);
    if (qs.values_in != TEST_POINTER_A) {
        printf("TEST -- qubits -- FAILED -- values_in second swap: Expected qs.values_in=%i but got %i.\n", TEST_POINTER_A, qs.values_in);
        exit(0);
    }
    if (qs.values_out != TEST_POINTER_B) {
        printf("TEST -- qubits -- FAILED -- values_out second swap: Expected qs.values_out=%i but got %i.\n", TEST_POINTER_B, qs.values_out);
        exit(0);
    }

    printf("TEST -- qubits -- SUCCESS\n");
}
