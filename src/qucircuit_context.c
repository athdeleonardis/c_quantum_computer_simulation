#include <stdlib.h>
#include "qucircuit_context.h"

qc_context_global qc_context_global_init(int num_qubits) {
    qc_context_global qccg;
    qccg.num_qubits = num_qubits;
    qccg.qubit_to_index = (int *)malloc(sizeof(int) * num_qubits);
    qccg.index_to_qubit = (int *)malloc(sizeof(int) * num_qubits);
    for (int i = 0; i < num_qubits; i++) {
        qccg.qubit_to_index[i] = i;
        qccg.index_to_qubit[i] = i;
    }
    return qccg;
}

qc_context_local qc_context_local_init(qc_context_local *qccl_outer, qucircuit *qc) {
    qc_context_local qccl;
    qccl.local_to_global_qubit = (int *)malloc(sizeof(int) * qc->num_inputs);
    if (qccl_outer == NULL)
        for (int i = 0; i < qc->num_inputs; i++)
            qccl.local_to_global_qubit[i] = i;
    else
        for (int i = 0; i < qc->num_inputs; i++) {
            qccl.local_to_global_qubit[i]
                = qccl_outer->local_to_global_qubit[qc->input_qubits[i]];
        }
    return qccl;
}

void qc_context_global_delete(qc_context_global qccg) {
    free(qccg.qubit_to_index);
    free(qccg.index_to_qubit);
}

void qc_context_local_delete(qc_context_local qccl) {
    free(qccl.local_to_global_qubit);
}

// e.g. want to make i0 be qx
// currently, i0->qy, qy->i0 and qx->iz, iz->qx
// Swap to be i0->qx, qx->i0 and qy->iz, iz->qy
void qc_context_global_fix(qc_context_global qccg, qc_context_local qccl, qucircuit *qc) {
    for (int i = 0; i < qc->num_inputs; i++) {
        int global_qubit = qccl.local_to_global_qubit[qc->input_qubits[i]]; // qx
        int index_prev = qccg.qubit_to_index[global_qubit]; // iz
        int qubit_prev = qccg.index_to_qubit[i]; // qy

        qccg.qubit_to_index[global_qubit] = i; // qx->i0
        qccg.index_to_qubit[i] = global_qubit; // i0->qx

        qccg.qubit_to_index[qubit_prev] = index_prev; // qy->iz
        qccg.index_to_qubit[index_prev] = qubit_prev; // iz->qy
    }
}
