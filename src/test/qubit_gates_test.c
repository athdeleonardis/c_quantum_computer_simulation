#include <stdio.h>
#include "../complex_matrices.h"
#include "../qubits.h"
#include "../qubit_gates.h"

int main(int argc, char *argv[]) {
    qubits *qin = qubits_alloc(3);
    qubits *qout0 = qubits_alloc(3);
    qubits *qout1 = qubits_alloc(3);

    printf("Initial qubit:\n");
    xiym_print(&qin->vals);

    for (int i = 0; i < qin->vals.rows; i++) {
        xiy val = { i, 0 };
        xiym_set(&qin->vals, val, 0, i);
    }

    printf("Test qubit:\n");
    xiym_print(&qin->vals);

    qubit_gate_x(0, 0, qin, qout0);

    qubits_free(qin);
    qubits_free(qout0);
    qubits_free(qout1);
}
