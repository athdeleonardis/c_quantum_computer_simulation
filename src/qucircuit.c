#include <stdlib.h>
#include "qucircuit.h"

void qucircuit_free(qucircuit *qc) {
    if (qc->input_qubits)
        free(qc->input_qubits);
    if (qc->input_indices)
        free(qc->input_indices);

    switch (qc->type) {
        case QC_TYPE_SEQUENTIAL:
            for (int i = 0; i < qc->subcircuits.num; i++) {
                qucircuit_free(qc->subcircuits.subcircuit+i);
            }
            break;
        case QC_TYPE_MATRIX:
            xiym_free(qc->matrix);
            break;
        case QC_TYPE_COMPILED:
            if (qc->compiled.matrix)
                xiym_free(qc->compiled.matrix);
            break;
    }

    free(qc);
}
