#ifndef QUANTUM_COMPUTER_SIMULATION
#define QUANTUM_COMPUTER_SIMULATION

#include "complex_matrices.h"
#include "qubits.h"

typedef struct qubit_array qubit_array;
typedef struct qubit_graph qubit_graph;
typedef void (*quantum_gate)(int num_inputs, int *inputs, qubits* in, qubits *out);
typedef struct quantum_circuit quantum_circuit;

void quantum_circuit_append(const char *name, int *qubits);
void quantum_circuit_evaluate(quantum_circuit *qc, qubits *in, qubits *out);
void quantum_circuit_simulate(quantum_circuit *qc, qubits *in, qubits *out, double noise);

struct quantum_circuit {
    int num_inputs;
    int *input_list;
    int is_gate;
    union {
        quantum_gate gate;
        struct {
            int num;
            quantum_circuit *subcircuits;
        } subcircuit;
    };
};

#endif
