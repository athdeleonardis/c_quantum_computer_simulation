#include "./qucircuit.h"

void qucircuit_init_2x2(qucircuit *circuit, char *name, xiy *mat_2x2) {
    circuit->type = QUCIRCUIT_TYPE_2X2;
    circuit->n_inputs = 1;
    circuit->name = name;
    circuit->mat = mat_2x2;
}

void qucircuit_init_4x4(qucircuit *circuit, char *name, xiy *mat_4x4) {
    circuit->type = QUCIRCUIT_TYPE_4X4;
    circuit->n_inputs = 2;
    circuit->name = name;
    circuit->mat = mat_4x4;
}

void qucircuit_init_parent(qucircuit *circuit, char *name, int n_inputs, int n_children, qucircuit_application *children) {
    circuit->type = QUCIRCUIT_TYPE_PARENT;
    circuit->n_inputs = n_inputs;
    circuit->name = name;
    circuit->n_children = n_children;
    circuit->children = children;
}

void qucircuit_init_func_u(qucircuit *circuit, char *name, qugate_func_u func_u) {
    circuit->type = QUCIRCUIT_TYPE_FUNC_U;
    circuit->n_inputs = 1;
    circuit->name = name;
    circuit->func_u = func_u;
}

void qucircuit_init_func_cu(qucircuit *circuit, char *name, qugate_func_cu func_cu) {
    circuit->type = QUCIRCUIT_TYPE_FUNC_CU;
    circuit->n_inputs = 2;
    circuit->name = name;
    circuit->func_cu = func_cu;
}

void qucircuit_init_func_mcu(qucircuit *circuit, char *name, int n_controls, qugate_func_mcu func_mcu) {
    circuit->type = QUCIRCUIT_TYPE_FUNC_MCU;
    circuit->n_inputs = n_controls + 1;
    circuit->n_controls = n_controls;
    circuit->func_mcu = func_mcu;
}

void qucircuit_init_func_mcmu(qucircuit *circuit, char *name, int n_controls, int n_targets, qugate_func_mcmu func_mcmu) {
    circuit->type = QUCIRCUIT_TYPE_FUNC_MCMU;
    circuit->n_inputs = n_controls + n_targets;
    circuit->n_controls = n_controls;
    circuit->n_targets = n_targets;
    circuit->func_mcmu = func_mcmu;
}
