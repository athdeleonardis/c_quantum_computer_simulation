#ifndef QUCIRCUIT
#define QUCIRCUIT

#include "qubits.h"
#include "qugate.h"

#define QC_TYPE_SEQUENTIAL 1
#define QC_TYPE_MATRIX 2 // Mostly ignoring for now
#define QC_TYPE_GATE 3
#define QC_TYPE_COMPILED 4

typedef struct qucircuit qucircuit;
typedef xiym *(*xiym_compiler)(int num_inputs, int *input_list, int num_qubits);

void qucircuit_free(qucircuit *q);

struct qucircuit {
    int num_inputs;
    int *input_qubits;
    int *input_indices;
    int type;
    int input_is_fixed;
    union {
        xiym *matrix;
        qugate gate;
        struct {
            int num;
            qucircuit *subcircuit;
        } subcircuits;
        struct {
            xiym *matrix;
            xiym_compiler compiler;
        } compiled;
    };
};

#endif
