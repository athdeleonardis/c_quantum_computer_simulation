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
    printf("Applied x gate to qubit 0\n");
    xiym_print(&qout0->vals);

    qubit_gate_y(0, 0, qin, qout0);
    printf("Applied y gate to qubit 0\n");
    xiym_print(&qout0->vals);

    int to_swap0[] = { 0, 1 };
    qubit_gate_swap(0, to_swap0, qin, qout0);
    printf("Swapped qubit 0 and 1\n");
    printf("Expected output:\n0 000 000 0\n1 001 010 2\n2 010 001 1\n3 011 011 3\n4 100 100 4\n5 101 110 6\n7 111 111 7\n");
    xiym_print(&qout0->vals);

    int to_swap1[] = { 1, 2 };
    qubit_gate_swap(0, to_swap1, qin, qout0);
    printf("Swapped qubit 1 and 2\n");
    printf("Expected output:\n0 000 000 0\n1 001 001 1\n2 010 100 4\n3 011 101 5\n4 100 010 2\n5 101 011 3\n6 110 110 6\n7 111 111 7\n");
    xiym_print(&qout0->vals);

    int to_swap2[] = { 2, 0 };
    qubit_gate_swap(0, to_swap0, qin, qout0);
    qubit_gate_swap(0, to_swap1, qout0, qout1);
    qubit_gate_swap(0, to_swap2, qout1, qout0);
    qubit_gate_swap(0, to_swap1, qout0, qout1);
    printf("Swapped qubits 01, 12, 20, 12 (Identity)\n");
    xiym_print(&qout1->vals);

    qubit_gate_cnot(0, 0, qin, qout0);
    printf("Applied cnot with control 0 target 1\n");
    printf("Expected output:\n0 000 000 0\n1 001 011 3\n2 010 010 2\n3 011 001 1\n4 100 100 4\n5 101 111 7\n6 110 110 6\n7 111 101 5\n");
    xiym_print(&qout0->vals);

    qubits_free(qin);
    qubits_free(qout0);
    qubits_free(qout1);
}
