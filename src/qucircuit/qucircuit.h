#ifndef QUCIRCUIT
#define QUCIRCUIT

#include "../complex_numbers/complex_numbers.h"

#define QUCIRCUIT_TYPE_2X2 1
#define QUCIRCUIT_TYPE_4X4 2
#define QUCIRCUIT_TYPE_PARENT 3

typedef struct qucircuit qucircuit;
typedef struct qucircuit_application qucircuit_application;

struct qucircuit {
    int type;
    int n_inputs;
    char *name;
    union {
        struct {
            xiy *mat;
        };
        struct {
            int n_children;
            qucircuit_application *children;
        };
    };
};

struct qucircuit_application {
    int *target_qubits;
    qucircuit *circuit;
};

/**
 * @brief Initialize a qucircuit that applies a 2x2 complex matrix.
 * 
 * @param circuit The qucircuit to initialize.
 * @param name The name to give the qucircuit.
 * @param mat_2x2 The 2x2 complex matrix the qucircuit applies.
 */
void qucircuit_init_2x2(qucircuit *circuit, char *name, xiy *mat_2x2);

/**
 * @brief Initialize a qucircuit that applies a 4x4 complex matrix.
 * 
 * @param circuit The qucircuit to initialize.
 * @param name The name to give the qucircuit.
 * @param mat_4x4 The 4x4 complex matrix the qucircuit applies.
 */
void qucircuit_init_4x4(qucircuit *circuit, char *name, xiy *mat_4x4);

/**
 * @brief Initialize a parent qucircuit that applies a series of child qucircuits.
 * 
 * @param circuit The parent qucircuit to initialize.
 * @param name The name to give the parent qucircuit.
 * @param n_inputs The number of input qubits the qucircuit takes.
 * @param children The child qucircuit applications for the parent qucircuit to apply.
 */
void qucircuit_init_parent(qucircuit *circuit, char *name, int n_inputs, int n_children, qucircuit_application *children);

#endif
