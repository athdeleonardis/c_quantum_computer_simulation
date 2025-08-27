#ifndef QUCIRCUIT
#define QUCIRCUIT

#include "../complex_numbers/complex_numbers.h"
#include "../qugate/qugate_func.h"

#define QUCIRCUIT_TYPE_2X2 1
#define QUCIRCUIT_TYPE_4X4 2
#define QUCIRCUIT_TYPE_PARENT 3
#define QUCIRCUIT_TYPE_FUNC_U 4
#define QUCIRCUIT_TYPE_FUNC_CU 5
#define QUCIRCUIT_TYPE_FUNC_MCU 6
#define QUCIRCUIT_TYPE_FUNC_MCMU 7

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
        struct {
            qugate_func_u func_u;
        };
        struct {
            qugate_func_cu func_cu;
        };
        struct {
            int n_controls;
            union {
                struct {
                    qugate_func_mcu func_mcu;
                };
                struct {
                    int n_targets;
                    qugate_func_mcmu func_mcmu;
                };
            };
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
 * @param n_inputs The number of input qubits the parent qucircuit takes.
 * @param n_children The number of children the parent qucircuit has.
 * @param children The child qucircuit applications for the parent qucircuit to apply.
 */
void qucircuit_init_parent(qucircuit *circuit, char *name, int n_inputs, int n_children, qucircuit_application *children);

/**
 * @brief Initializes a qucircuit that applies a qugate function with a single target qubit.
 * 
 * @param circuit The qucircuit to initialize.
 * @param name The name to give the qucircuit.
 * @param func_u The qugate function to apply to the target qubit.
 */
void qucircuit_init_func_u(qucircuit *circuit, char *name, qugate_func_u func_u);

/**
 * @brief Initializes a qucircuit that applies a qugate function with a single control qubit and single target qubit.
 * 
 * @param circuit The qucircuit to initialize.
 * @param name The name to give the qucircuit.
 * @param func_cu The qugate function to apply to the single control and target qubits.
 */
void qucircuit_init_func_cu(qucircuit *circuit, char *name, qugate_func_cu func_cu);

/**
 * @brief Initializes a qucircuit that applies a qugate function with multiple control qubits and a single target qubit.
 * 
 * @param circuit The qucircuit to initialize.
 * @param name The name to give the qucircuit.
 * @param n_controls The number of control qubits for the qugate.
 * @param func_mcu The qugate function to apply to the multiple control qubits and single target qubit.
 */
void qucircuit_init_func_mcu(qucircuit *circuit, char *name, int n_controls, qugate_func_mcu func_mcu);

/**
 * @brief Initializes a qucircuit that applies a qugate function with multiple control and multiple target qubits.
 * 
 * @param circuit The qucircuit to initialize.
 * @param name The name to give the qucircuit.
 * @param n_controls The number of control qubits for the qugate.
 * @param n_targets The number of target qubits for the qugate.
 * @param func_mcmu The qugate function to apply to the multiple control qubits and multiple target qubits.
 */
void qucircuit_init_func_mcmu(qucircuit *circuit, char *name, int n_controls, int n_targets, qugate_func_mcmu func_mcmu);

#endif
