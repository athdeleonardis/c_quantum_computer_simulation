#include "../qubits/qubits_apply.h"
#include "./qucircuit_apply.h"

void qucircuit_apply_2x2(qubits qs, qucircuit_context qcc, qucircuit *qc);
void qucircuit_apply_4x4(qubits qs, qucircuit_context qcc, qucircuit *qc);
void qucircuit_apply_parent(qubits qs, qucircuit_context qcc, qucircuit *qc);

void qucircuit_apply(qubits qs, qucircuit_context qcc, qucircuit_application *application) {
    qucircuit_context qccn = qucircuit_context_push(&qcc, application->circuit->n_inputs, application->target_qubits);
    // qucircuit_application no longer required, as qccn contains the true inputs to the qucircuit.

    switch (application->circuit->type) {
        case QUCIRCUIT_TYPE_2X2: {
            qucircuit_apply_2x2(qs, qcc, application->circuit);
        }
        case QUCIRCUIT_TYPE_4X4: {
            qucircuit_apply_4x4(qs, qcc, application->circuit);
        }
        case QUCIRCUIT_TYPE_PARENT: {
            qucircuit_apply_parent(qs, qcc, application->circuit);
        }
    }
}

void qucircuit_apply_2x2(qubits qs, qucircuit_context qcc, qucircuit *qc) {
    int q = qcc.input_to_qubit_stack[0];
    qubits_apply_2x2(&qs, qc->mat, q);
}

void qucircuit_apply_4x4(qubits qs, qucircuit_context qcc, qucircuit *qc) {
    int q1 = qcc.input_to_qubit_stack[0];
    int q2 = qcc.input_to_qubit_stack[1];
    qubits_apply_4x4(&qs, qc->mat, q1, q2);
}

void qucircuit_apply_parent(qubits qs, qucircuit_context qcc, qucircuit *qc) {
    for (int i = 0; i < qc->n_children; i++) {
        qucircuit_apply(qs, qcc, qc->children+i);
    }
}
