#ifndef QUANTUM_COMPUTER_SIMULATION
#define QUANTUM_COMPUTER_SIMULATION

typedef struct qubit_array qubit_array;
typedef struct qubit_graph qubit_graph;
typedef struct quantum_circuit quantum_circuit;
void quantum_circuit_append(const char *name, int *qubits);
void quantum_circuit_evaluate(quantum_circuit *qc, qubit_array *in, qubit_array *out);
void quantum_circuit_simulate(quantum_circuit *qc, qubit_array *in, qubit_array *out, double noise);

#endif
