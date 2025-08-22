#ifndef QUBITS
#define QUBITS

#include "../complex_numbers/complex_numbers.h"

typedef struct qubits qubits;

/**
 * @brief Initialize qubits with space for input and output values of computations.
 * 
 * @param qs The qubits to be initialized.
 * @param n_qubits The number of qubits.
 * @param values_in The space for inputs of computations.
 * @param values_out The space for outputs of computations.
 */
void qubits_init(qubits *qs, int n_qubits, xiy *values_in, xiy *values_out);

/**
 * @brief Swaps the input and output values of the qubits.
 * 
 * @param qs The qubits to have its input and output values swapped.
 */
void qubits_swap_in_out(qubits *qs);

struct qubits {
    int n_qubits;
    int n_values;
    xiy *values_in;
    xiy *values_out;
};

#endif
