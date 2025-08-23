#ifndef QUCIRCUIT_CONTEXT
#define QUCIRCUIT_CONTEXT

typedef struct qucircuit_context qucircuit_context;

struct qucircuit_context {
    int n_qubits;
    int *input_to_qubit_stack;
};

/**
 * @brief Initialize a qucircuit context with N qubits
 * 
 * @param n_qubits The numbers of qubits the qucircuit context has
 * @param stack The integer pointer to contain the input to qubit mapping (Set to 0,1,...,n_qubits-1)
 */
qucircuit_context qucircuit_context_init(int n_qubits, int *stack);

/**
 * @brief Returns a new qucontext, with N qubits, putting the remapped inputs onto the input to qubit mapping stack.
 * 
 * Example 1: qcc = [0,1,2,3,4], inputs = [1,2], qccn = [1,2].
 * 
 * Example 2: qcc = [1,4,7,10,12], inputs = [1,2,4], qccn = [4,7,12].
 * 
 * @param qcc The qucircuit context to remap via the given inputs.
 * @param n_inputs The number of qubits to remap.
 * @param inputs The qubits to remap.
 * 
 * @returns The new context with mapping from input to qubit.
 */
qucircuit_context qucircuit_context_push(qucircuit_context *qcc, int n_inputs, int *inputs);

#endif
