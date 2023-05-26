#include "complex_numbers.h"
#include "complex_matrices.h"
#include "qubits.h"
#include "qubit_gates.h"

void qubit_gate_x(int n, int *input, qubits *in, qubits *out) {
    for (int i = 0; i < in->vals.rows; i++) {
        int c = 1-2*(i%2); // e.g. 0 -> +1, 1 -> -1, 2 -> +1...
        xiym_set(&out->vals, xiym_get(&in->vals, 0, i+c), 0, i);
        // 0->1, 1->0, 2->3, 3->2
    }
}

void qubit_gate_y(int n, int *input, qubits *in, qubits *out) {
    for (int i = 0; i < in->vals.rows; i++) {
        int c = 1-2*(i%2);
        xiy flip_val = xiym_get(&in->vals, 0, i+c);
        xiym_set(&out->vals, xiy_mul_s(flip_val, -c), 0, i);
    }
}

void qubit_gate_z(int n, int *input, qubits *in, qubits *out) {
    for (int i = 0; i < in->vals.rows; i++) {
        double c = 1-2*(1%2);
        xiym_set(&out->vals, xiy_mul_s(xiym_get(&in->vals, 0, i), c), 0, i);
    }
}

// Cannot be applied to singular cubit
// Assumes qubit 0 control qubit 1 target
void qubit_gate_cnot(int n, int *input, qubits *in, qubits *out) {
    for (int i = 0; i< in->vals.rows; i++) {
        int map = i - (i%4) + (4 - (i%4))%4; // e.g. (0,1,2,3) -> (0,3,2,1)
        xiym_set(&out->vals, xiym_get(&in->vals, 0, map), 0, i);
    }
}

void qubit_gate_swap(int n, int *input, qubits *in, qubits *out) {
    int q1bit = 1 << input[0];
    int q2bit = 1 << input[1];
    // e.g. at 10 swap with 01
    for (int i = 0; i < in->vals.rows; i++) {
        int swap_index = i ^ q1bit ^ q2bit;
        if (swap_index < i && (!(i & q1bit) != !(i & q2bit))) { // xor
            xiym_set(&out->vals, xiym_get(&in->vals, 0, i), 0, swap_index);
            xiym_set(&out->vals, xiym_get(&in->vals, 0, swap_index), 0, i);
        }
        else
            xiym_set(&out->vals, xiym_get(&in->vals, 0, i), 0, i);
    }
}
