#include "./qucircuit.h"

void qucircuit_init_2x2(qucircuit_t *circuit, char *name, xiy *mat_2x2) {
    circuit->type = QUCIRCUIT_TYPE_2X2;
    circuit->n_inputs = 1;
    circuit->name = name;
    circuit->mat = mat_2x2;
}

void qucircuit_init_4x4(qucircuit_t *circuit, char *name, xiy *mat_4x4) {
    circuit->type = QUCIRCUIT_TYPE_4X4;
    circuit->n_inputs = 2;
    circuit->name = name;
    circuit->mat = mat_4x4;
}

void qucircuit_init_parent(qucircuit_t *circuit, char *name, int n_inputs, qucircuit_application_t *children) {
    circuit->type = QUCIRCUIT_TYPE_PARENT;
    circuit->n_inputs = n_inputs;
    circuit->name = name;
    circuit->children = children;
}
