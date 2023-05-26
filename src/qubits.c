#include <stdlib.h>
#include "complex_numbers.h"
#include "complex_matrices.h"
#include "qubits.h"

qubits *qubits_alloc(int n) {
    qubits *qbs = (qubits *)malloc(sizeof(qubits));
    qbs->n = n;
    qbs->vals.cols = 1;
    qbs->vals.rows = 1 << n;
    qbs->vals.values = (xiy *)malloc(sizeof(xiy) * qbs->vals.rows);
    xiym_set(&qbs->vals, xiy_one, 0, 0);
    for (int i = 1; i < qbs->vals.rows; i++)
        xiym_set(&qbs->vals, xiy_zero, 0, i);
    return qbs;
}

void qubits_free(qubits *qbs) {
    free(&qbs->vals);
    free(qbs);
}
