#ifndef QUCIRCUIT_CONTEXT
#define QUCIRCUIT_CONTEXT

#include "qucircuit.h"

typedef struct qc_context_global qc_context_global;
typedef struct qc_context_local qc_context_local;

qc_context_global qc_context_global_init(int num_global_qubits);
qc_context_local qc_context_local_init(qc_context_local *qccl_outer, qucircuit *qc);
void qc_context_global_delete(qc_context_global qccg);
void qc_context_local_delete(qc_context_local qccl);
void qc_context_global_fix(qc_context_global qccg, qc_context_local qccl, qucircuit *qc);

struct qc_context_global {
    int num_qubits;
    int *qubit_to_index;
    int *index_to_qubit;
};

struct qc_context_local {
    int *local_to_global_qubit;
};

#endif
