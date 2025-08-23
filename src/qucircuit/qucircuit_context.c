#include "./qucircuit_context.h"

qucircuit_context qucircuit_context_init(int n_qubits, int *stack) {
    for (int i = 0; i < n_qubits; i++) {
        stack[i] = i;
    }
    qucircuit_context qcc = { .n_qubits=n_qubits, .input_to_qubit_stack=stack };
    return qcc;
}

qucircuit_context qucircuit_context_push(qucircuit_context *qcc, int n_inputs, int *inputs) {
    int *stack_new = qcc->input_to_qubit_stack + qcc->n_qubits;
    for (int i = 0; i < n_inputs; i++) {
        stack_new[i] = qcc->input_to_qubit_stack[inputs[i]];
    }
    qucircuit_context qccn = { .n_qubits=n_inputs, .input_to_qubit_stack=stack_new };
    return qccn;
}
