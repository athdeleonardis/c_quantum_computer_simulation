#ifndef QUANTUM_COMPUTER_SIMULATION
#define QUANTUM_COMPUTER_SIMULATION

#include "complex_matrices.h"

typedef struct qubit_array qubit_array;
typedef struct qubit_graph qubit_graph;
typedef void (*quantum_gate)(int num_inputs, int *inputs, qubit_array* in, qubit_array *out);
typedef struct quantum_circuit quantum_circuit;

void quantum_circuit_append(const char *name, int *qubits);
void quantum_circuit_evaluate(quantum_circuit *qc, qubit_array *in, qubit_array *out);
void quantum_circuit_simulate(quantum_circuit *qc, qubit_array *in, qubit_array *out, double noise);

struct qubit_array {
    int n;
    xiym *vals;
};

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
