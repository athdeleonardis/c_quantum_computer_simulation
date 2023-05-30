#ifndef QUANTUM_GATES
#define QUANTUM_GATES

#include "qubits.h"

typedef void (*qugate)(int num_inputs, int *inputs, qubits* in, qubits *out);

// Assume acting on the first qubit
void qugate_q0x(int, int *input, qubits *in, qubits *out);
void qugate_q0y(int, int *input, qubits *in, qubits *out);
void qugate_q0z(int, int *input, qubits *in, qubits *out);
// Assume first qubit is control, second is target
void qugate_q01cnot(int, int *inputs, qubits *in, qubits *out);

// Swaps qubit a with qubit b
void qugate_swap(int, int *inputs, qubits *in, qubits *out);

#endif
