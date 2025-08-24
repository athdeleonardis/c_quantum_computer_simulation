#include "../../src/qucircuit/qucircuit.h"

#define POINTER_2X2_NAME (char *)1
#define POINTER_2X2_MAT (xiy *)2
#define POINTER_4X4_NAME (char *)3
#define POINTER_4X4_MAT (xiy *)4
#define POINTER_PARENT_NAME (char *)5
#define PARENT_N_INPUTS 3
#define PARENT_N_CHILDREN 2
#define POINTER_PARENT_CHILDREN (qucircuit_application *)6

int main(int argc, char *argv) {
    qucircuit qc_2x2;
    qucircuit_init_2x2(&qc_2x2, POINTER_2X2_NAME, POINTER_2X2_MAT);
    if (qc_2x2.type != QUCIRCUIT_TYPE_2X2) {
        printf("TEST -- qucircuit -- FAILED -- 2x2 type: Expected type=%i but got %i\n", QUCIRCUIT_TYPE_2X2, qc_2x2.type);
        exit(0);
    }
    if (qc_2x2.name != POINTER_2X2_NAME) {
        printf("TEST -- qucircuit -- FAILED -- 2x2 name: Expected name=%i but got %i\n", POINTER_2X2_NAME, qc_2x2.name);
        exit(0);
    }
    if (qc_2x2.n_inputs != 1) {
        printf("TEST -- qucircuit -- FAILED -- 2x2 n_inputs: Expected n_inputs=1 but got %i\n", qc_2x2.n_inputs);
        exit(0);
    }
    if (qc_2x2.mat != POINTER_2X2_MAT) {
        printf("TEST -- qucircuit -- FAILED -- 2x2 mat: Expected mat=%i but got %i\n", POINTER_2X2_MAT, qc_2x2.mat);
        exit(0);
    }
    qucircuit qc_4x4;
    qucircuit_init_4x4(&qc_4x4, POINTER_4X4_NAME, POINTER_4X4_MAT);
    if (qc_4x4.type != QUCIRCUIT_TYPE_4X4) {
        printf("TEST -- qucircuit -- FAILED -- 4x4 type: Expected type=%i but got %i\n", QUCIRCUIT_TYPE_4X4, qc_4x4.type);
        exit(0);
    }
    if (qc_4x4.name != POINTER_4X4_NAME) {
        printf("TEST -- qucircuit -- FAILED -- 4x4 name: Expected name=%i but got %i\n", POINTER_4X4_NAME, qc_4x4.name);
        exit(0);
    }
    if (qc_4x4.n_inputs != 2) {
        printf("TEST -- qucircuit -- FAILED -- 4x4 n_inputs: Expected n_inputs=2 but got %i\n", qc_4x4.n_inputs);
        exit(0);
    }
    if (qc_4x4.mat != POINTER_4X4_MAT) {
        printf("TEST -- qucircuit -- FAILED -- 4x4 mat: Expected mat=%i but got %i\n", POINTER_4X4_MAT, qc_4x4.mat);
        exit(0);
    }

    // not used haha
    int target_qubits[2] = { 0, 1 };
    qucircuit_application qca_2x2 = { .target_qubits=target_qubits, .circuit=&qc_2x2 };
    qucircuit_application qca_4x4 = { .target_qubits=target_qubits, .circuit=&qc_4x4 };
    qucircuit_application qcas[PARENT_N_CHILDREN] = {
        qca_2x2,
        qca_4x4
    };

    qucircuit qc_parent;
    qucircuit_init_parent(&qc_parent, POINTER_PARENT_NAME, PARENT_N_INPUTS, PARENT_N_CHILDREN, POINTER_PARENT_CHILDREN);
    if (qc_parent.type != QUCIRCUIT_TYPE_PARENT) {
        printf("TEST -- qucircuit -- FAILED -- parent type: Expected type=%i but got %i\n", QUCIRCUIT_TYPE_PARENT, qc_parent.type);
        exit(0);
    }
    if (qc_parent.name != POINTER_PARENT_NAME) {
        printf("TEST -- qucircuit -- FAILED -- parent name: Expected name=%i but got %i\n", POINTER_PARENT_NAME, qc_parent.name);
        exit(0);
    }
    if (qc_parent.n_inputs != PARENT_N_INPUTS) {
        printf("TEST -- qucircuit -- FAILED -- parent n_inputs: Expected n_inputs=%i but got %i\n", PARENT_N_INPUTS, qc_parent.n_inputs);
        exit(0);
    }
    if (qc_parent.n_children != PARENT_N_CHILDREN) {
        printf("TEST -- qucircuit -- FAILED -- parent n_children: Expected n_children=%i but got %i\n", PARENT_N_CHILDREN, qc_parent.n_children);
        exit(0);
    }
    if (qc_parent.children != POINTER_PARENT_CHILDREN) {
        printf("TEST -- qucircuit -- FAILED -- parent n_children: Expected children=%i but got %i\n", POINTER_PARENT_CHILDREN, qc_parent.children);
        exit(0);
    }

    printf("TEST -- qucircuit -- SUCCESS\n");
}
