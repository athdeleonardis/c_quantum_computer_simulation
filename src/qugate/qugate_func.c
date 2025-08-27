#include "./qugate_func.h"

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
