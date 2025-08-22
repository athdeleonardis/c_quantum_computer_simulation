#include "./qubits.h"

void qubits_init(qubits *qs, int n_qubits, xiy *values_in, xiy *values_out) {
    qs->n_qubits = n_qubits;
    qs->n_values = 1 << n_qubits;
    qs->values_in = values_in;
    qs->values_out = values_out;
}

void qubits_swap_in_out(qubits *qs) {
    xiy *temp = qs->values_in;
    qs->values_in = qs->values_out;
    qs->values_out = temp;
}
