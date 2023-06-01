#include <math.h>
#include "complex_numbers.h"
#include "complex_matrices.h"
#include "qubits.h"
#include "qugate.h"

void qugate_q0x(int n, int *input, qubits *in, qubits *out) {
    for (int i = 0; i < in->vals.rows; i++) {
        int c = 1-2*(i%2); // e.g. 0 -> +1, 1 -> -1, 2 -> +1...
        xiym_set(&out->vals, xiym_get(&in->vals, 0, i+c), 0, i);
        // 0->1, 1->0, 2->3, 3->2
    }
}

void qugate_q0y(int n, int *input, qubits *in, qubits *out) {
    for (int i = 0; i < in->vals.rows; i++) {
        int c = 1-2*(i%2);
        xiy flip_val = xiym_get(&in->vals, 0, i+c);
        xiym_set(&out->vals, xiy_mul_s(flip_val, -c), 0, i);
    }
}

void qugate_q0z(int n, int *input, qubits *in, qubits *out) {
    for (int i = 0; i < in->vals.rows; i++) {
        double c = 1-2*(1%2);
        xiym_set(&out->vals, xiy_mul_s(xiym_get(&in->vals, 0, i), c), 0, i);
    }
}

void qugate_q0h(int n, int *input, qubits *in, qubits *out) {
    double c = 1/sqrt(2);
    for (int i = 0; i < in->vals.rows; i++) {
        int map = 1-2*(i%2); // 1, -1, 1, -1...
        xiy val1 = xiym_get(&in->vals, 0, i);
        val1 = xiy_mul_s(val1, -1*map);
        xiy val2 = xiym_get(&in->vals, 0, i+map);
        xiy val = xiy_mul_s(xiy_add(val1, val2), c);
        xiym_set(&out->vals, val, 0, i);
    }
}

// Cannot be applied to singular cubit
// Assumes qubit 0 control qubit 1 target
void qugate_q01cnot(int n, int *input, qubits *in, qubits *out) {
    for (int i = 0; i< in->vals.rows; i++) {
        int map = i - (i%4) + (4 - (i%4))%4; // e.g. (0,1,2,3) -> (0,3,2,1)
        xiym_set(&out->vals, xiym_get(&in->vals, 0, map), 0, i);
    }
}

void qugate_swap(int n, int *input, qubits *in, qubits *out) {
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
