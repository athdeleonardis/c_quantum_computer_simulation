#define _USE_MATH_DEFINES
#include <math.h>
#include "./qugate_func.h"

//
// 'qugate_func.c' function definitions
//

/**
 * @brief Counts the number of bits set to 1.
 * 
 * @param n The number to count the number of bits of.
 */
int _qugate_func_count_bits(int n);

/**
 * @brief Returns n mod m, but positive.
 */
int _qugate_func_positive_mod(int n, int m);

//
// 'qugate_func.h' function implementations
//

/* qugate_func_u */

void qugate_func_x(qubits *qs, int q) {
    int q_set_1 = 1 << q;

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        qs->values_out[s] = qs->values_in[s ^ q_set_1];
    }

    qubits_swap_in_out(qs);
}

void qugate_func_y(qubits *qs, int q) {
    int q_set_1 = 1 << q;

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & q_set_1) {
            qs->values_out[s] = xiy_mul(xiy_i, qs->values_in[s ^ q_set_1]);
            continue;
        }
        qs->values_out[s] = xiy_mul(xiy_mul_s(xiy_i, -1), qs->values_in[s ^ q_set_1]);
    }

    qubits_swap_in_out(qs);
}

void qugate_func_z(qubits *qs, int q) {
    int q_set_1 = 1 << q;

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & q_set_1) {
            qs->values_in[s] = xiy_mul_s(qs->values_in[s], -1);
        }
    }
}

void qugate_func_h(qubits *qs, int q) {
    int q_set_1 = 1 << q;
    int q_set_0 = ~q_set_1;

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        // If q=1, take (0)-(1), if q=0, take (0)+(1)
        xiy v0 = qs->values_in[s & q_set_0];
        xiy v1 = xiy_mul_s(qs->values_in[s | q_set_1], -!!(s & q_set_1));
        qs->values_out[s] = xiy_mul_s(xiy_add(v0, v1), M_SQRT1_2);
    }

    qubits_swap_in_out(qs);
}

/* qugate_func_cu */

void qugate_func_cx(qubits *qs, int qc, int qt) {
    int qc_set_1 = 1 << qc;
    int qt_set_1 = 1 << qt;

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & qc_set_1) {
            qs->values_out[s] = qs->values_in[s ^ qt_set_1];
            continue;
        }
        qs->values_out[s] = qs->values_in[s];
    }

    qubits_swap_in_out(qs);
}

void qugate_func_cy(qubits *qs, int qc, int qt) {
    int qc_set_1 = 1 << qc;
    int qt_set_1 = 1 << qt;

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & qc_set_1) {
            if (s & qt_set_1) {
                qs->values_out[s] = xiy_mul(xiy_i, qs->values_in[s ^ qt_set_1]);
                continue;
            }
            qs->values_out[s] = xiy_mul(xiy_mul_s(xiy_i, -1), qs->values_in[s ^ qt_set_1]);
            continue;
        }
        qs->values_out[s] = qs->values_in[s];
    }

    qubits_swap_in_out(qs);
}

void qugate_func_cz(qubits *qs, int qc, int qt) {
    int selector = (1 << qc) | (1 << qt);

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & selector == selector) {
            qs->values_in[s] = xiy_mul_s(qs->values_in[s], -1);
        }
    }
}

void qugate_func_swap(qubits *qs, int qc, int qt) {
    int qc_set_1 = 1 << qc;
    int qt_set_1 = 1 << qt;
    int qc_swap = (qc_set_1 ^ qc_swap);

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        int swapper = (!!(s & qc_set_1) ^ !!(s & qc_set_1)) * qc_swap; // if qc=qt, swapper=0, if qc != qt, swapper = qc_swap;
        qs->values_out[s] = qs->values_in[s ^ swapper]; 
    }

    qubits_swap_in_out(qs);
}

/* qugate_func_mu */

void qugate_func_mx(qubits *qs, int n_targets, int *inputs) {
    int flip = 0;
    for (int i = 0; i < n_targets; i++) {
        flip |= 1 << inputs[i];
    }

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        qs->values_out[s] = qs->values_out[s ^ flip];
    }

    qubits_swap_in_out(qs);
}

void qugate_func_my(qubits *qs, int n_targets, int *inputs) {
    int flip = 0;
    for (int i = 0; i < n_targets; i++) {
        flip |= 1 << inputs[i];
    }

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        // Every target set to 1 (n1), multiply i, every target set to 0 (n0), multiply by -i (i^-1)
        // i.e. multiply by i^(n1-n0)
        int ones = s & flip;
        // Count the bits in s1
        // n1=bit_count, n0=n_targets-bit_count, multiply by i^(2*bit_count-n_targets)
        int power = _qugate_func_positive_mod(2 * _qugate_func_count_bits(ones) - n_targets, 4);
        // i^0=1, i^1=i, i^2=-1, i^3=-i
        if (power % 2) {
            // power=1, 2-power=1
            // power=3, 2-power=-1
            qs->values_out[s] = xiy_mul(xiy_mul_s(xiy_i, 2-power), qs->values_in[s ^ flip]);
            continue;
        }
        // power=0, 1-power=1
        // power=2, 1-power=-1
        qs->values_out[s] = xiy_mul_s(qs->values_in[s ^ flip], 1-power);
    }

    qubits_swap_in_out(qs);
}

void qugate_func_mz(qubits *qs, int n_targets, int *inputs) {
    int selector = 0;
    for (int i = 0; i < n_targets; i++) {
        selector |= 1 << inputs[i];
    }

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        int ones = s & selector;
        // See 'qugate_func_my' comments for similar code but more comments.
        int power = _qugate_func_positive_mod(2 * _qugate_func_count_bits(ones) - n_targets, 2);
        if (power) {
            qs->values_in[s] = xiy_mul_s(qs->values_in[s], -1);
        }
    }
}

void qugate_func_mh(qubits *qs, int n_targets, int *inputs) {
    // TODO(): Is there something better than this? Probably not.
    for (int i = 0; i < n_targets; i++) {
        qugate_func_h(qs, inputs[i]);
    }
}

/* qugate_func_mcu */

void qugate_func_mcx(qubits *qs, int n_controls, int *inputs) {
    int selector = 0;
    for (int i = 0; i < n_controls; i++) {
        selector |= 1 << inputs[i];
    }
    int qt_set_1 = 1 << inputs[n_controls];

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & selector == selector) {
            qs->values_out[s] = qs->values_in[s ^ qt_set_1];
            continue;
        }
        qs->values_out[s] = qs->values_out[s];
    }

    qubits_swap_in_out(qs);
}

void qugate_func_mcy(qubits *qs, int n_controls, int *inputs) {
    int selector = 0;
    for (int i = 0; i < n_controls; i++) {
        selector |= 1 << inputs[i];
    }
    int qt_set_1 = 1 << inputs[n_controls];

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & selector == selector) {
            if (s & qt_set_1) {
                qs->values_out[s] = xiy_mul(xiy_i, qs->values_in[s ^ qt_set_1]);
                continue;
            }
            qs->values_out[s] = xiy_mul(xiy_mul_s(xiy_i, -1), qs->values_in[s ^ qt_set_1]);
            continue;
        }
        qs->values_out[s] = qs->values_in[s];
    }

    qubits_swap_in_out(qs);
}

void qugate_func_mcz(qubits *qs, int n_controls, int *inputs) {
    int selector = 0;
    for (int i = 0; i < n_controls + 1; i++) {
        selector |= 1 << inputs[i];
    }

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & selector == selector) {
            qs->values_in[s] = xiy_mul_s(qs->values_in[s], -1);
        }
    }
}

void qugate_func_mch(qubits *qs, int n_controls, int *inputs) {
    int selector = 0;
    for (int i = 0; i < n_controls; i++) {
        selector |= inputs[i];
    }
    int qt_set_1 = 1 << inputs[n_controls];
    int qt_set_0 = ~qt_set_1;

    int n_values = qs->n_values;
    for (int s = 0; s < n_values; s++) {
        if (s & selector == selector) {
            // See 'qugate_func_h' for similar code but with more comments
            xiy v0 = qs->values_in[s & qt_set_0];
            xiy v1 = xiy_mul_s(qs->values_in[s | qt_set_1], -!!(s & qt_set_1));
            qs->values_out[s] = xiy_mul_s(xiy_add(v0, v1), M_SQRT1_2);
            continue;
        }
        qs->values_out[s] = qs->values_in[s];
    }

    qubits_swap_in_out(qs);
}

/* qugate_func_mcmu */

//
// 'qugate_func.h' function implementations
//

int _qugate_func_count_bits(int n) {
    // Kernighan's Algorithm
    int count = 0;
    while (n) {
        n &= n - 1;
        count++;
    }
    return count;
}

int _qugate_func_positive_mod(int n, int m) {
    return (n % m + m) % m;
}
