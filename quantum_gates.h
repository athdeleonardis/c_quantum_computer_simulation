#ifndef QUANTUM_GATES
#define QUANTUM_GATES

void quantum_gate_x(int, int *input, qubit_array *in, qubit_array *out);
void quantum_gate_y(int, int *input, qubit_array *in, qubit_array *out);
void quantum_gate_z(int, int *input, qubit_array *in, qubit_array *out);
void quantum_gate_cnot(int, int *inputs, qubit_array *in, qubit_array *out);

#endif
