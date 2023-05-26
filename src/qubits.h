#ifndef QUBITS
#define QUBITS

#include "complex_matrices.h"

typedef struct qubits qubits;

qubits *qubits_alloc(int n);
void qubits_free(qubits *qbs);

struct qubits {
    int n;
    xiym vals;
};

#endif
