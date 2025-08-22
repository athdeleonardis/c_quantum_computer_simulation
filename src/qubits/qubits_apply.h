#ifndef QUBITS_APPLY
#define QUBITS_APPLY

#include "./qubits.h"

/**
 * @brief Apply a 2x2 complex matrix to a qubit state with a particular qubit as the target.
 * 
 * @param qs The qubit state to apply the matrix to.
 * @param mat The 2x2 matrix to apply to the state.
 * @param q The particular qubit the matrix is targetting.
 */
void qubits_apply_2x2(qubits *qs, xiy *mat_2x2, int q);

/**
 * @brief Apply a 4x4 complex to a qubit state with two particular qubits as the targets.
 * 
 * @param qs The qubit state to apply the matrix to.
 * @param mat The 4x4 matrix to apply to the state.
 * @param q1 The first particular qubit the matrix is targetting.
 * @param q2 The second particular qubit the matrix is targetting.
 */
void qubits_apply_4x4(qubits *qs, xiy *mat_4x4, int q1, int q2);

#endif
