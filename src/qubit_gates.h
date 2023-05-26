#ifndef QUANTUM_GATES
#define QUANTUM_GATES

#include "qubits.h"

// Assume acting on the first qubit
void qubit_gate_x(int, int *input, qubits *in, qubits *out);
void qubit_gate_y(int, int *input, qubits *in, qubits *out);
void qubit_gate_z(int, int *input, qubits *in, qubits *out);
// Assume first qubit is control, second is target
void qubit_gate_cnot(int, int *inputs, qubits *in, qubits *out);
// Swaps qubit a with qubit b
void qubit_gate_swap(int, int *inputs, qubits *in, qubits *out);

#endif
