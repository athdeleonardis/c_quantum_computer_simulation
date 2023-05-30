#ifndef QUANTUM_COMPUTER_SIMULATION
#define QUANTUM_COMPUTER_SIMULATION

#include "complex_matrices.h"
#include "qubits.h"
#include "qucircuit.h"

typedef struct qubit_graph qubit_graph;
typedef void (*qugate)(int num_inputs, int *inputs, qubits* in, qubits *out);

void qucircuit_evaluate(qucircuit *qc, qubits *in, qubits *out);
void qucircuit_simulate(qucircuit *qc, qubits *in, qubits *out, double noise);
qucircuit *qucircuit_alloc(int num_inputs, int *input_list, int type);

#endif
